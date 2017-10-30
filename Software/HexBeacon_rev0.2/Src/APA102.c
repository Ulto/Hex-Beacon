#include "APA102.h"

#include "spi.h"



/*
 * APA102_Update - Initiates DMA transmit of current pixel data.  Scales channel brightness to fit
 *                 within specified available power (APA102_MAX_CURRENT).
 *  arguments:
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_Update()
{
    // Variable Declarations
    uint32_t requiredCurrent = 0;
    float    scalingFactor   = 0;
    uint32_t position        = 0;
    uint32_t pixel           = 0;

    // Confirm that update isn't already underway.
    if (APA102_stripStatus1 == APA102_UPDATING)
    {
        return APA102_SUCCESS;
    }

    // Indicate that APA102 strip update is underway.
    APA102_stripStatus1 = APA102_UPDATING;

    // Check power requirements and scale to suit, if enabled.
    if (APA102_CURRENT_LIMIT_ENABLE == 1)
    {
        // Calculate power needs of current frame.
        for (pixel = 0; pixel < APA102_STRIPLEN; pixel++)
        {
            // Calculate desired pixel data's position in the strip array.
            position = (APA102_START_FRAME_BYTES + (pixel * APA102_BYTES_PER_PIXEL));

            // Convert intensity value into current consumption and add to tally.
            requiredCurrent += APA102_Intensity_To_Current(APA102_Strip[position + 1]);    // RED Channel
            requiredCurrent += APA102_Intensity_To_Current(APA102_Strip[position + 2]);    // GRN Channel
            requiredCurrent += APA102_Intensity_To_Current(APA102_Strip[position + 3]);    // BLU Channel
        }

        // Determine scaling factor and scale back, if needed.
        if (requiredCurrent > APA102_MAX_CURRENT)
        {
        	// Determine Scaling Factor
            scalingFactor = ((float) APA102_MAX_CURRENT / (float) requiredCurrent);

            // Apply Scaling Factor
            for (pixel = 0; pixel < APA102_STRIPLEN; pixel++)
            {
            	// Calculate position of the desired pixel data in the strip array.
                position = (APA102_START_FRAME_BYTES + (pixel * APA102_BYTES_PER_PIXEL));

                // Convert intensity value into current consumption and add to tally.
                APA102_Strip[position + 1] *= scalingFactor;	// RED Channel
                APA102_Strip[position + 2] *= scalingFactor;    // GRN Channel
                APA102_Strip[position + 3] *= scalingFactor;  	// BLU Channel
            }
        }
    }

    // Copy pixel data into output buffer.
    memcpy(APA102_Strip_Buffer, APA102_Strip, APA102_STRIP_UPDATE_PACKET_BYTES);

    // Initiate DMA transmit of current pixel data.  Check HAL return status.
    if (HAL_SPI_Transmit_DMA(&APA102_SPI_HANDLE, APA102_Strip_Buffer, APA102_STRIP_UPDATE_PACKET_BYTES) != HAL_OK)
    {
        APA102_stripStatus1 = APA102_ERROR;
        return APA102_FAILURE;
    }
    else
    {
        return APA102_SUCCESS;
    }
}


/*
 * APA102_Init - Initializes array containing pixel data.
 *  arguments:
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_Init()
{
    // Set strip status to UNKNOWN when initialized.
    APA102_stripStatus1 = APA102_UNKNOWN;

    // Sanity check strip length
    if (APA102_STRIPLEN > APA102_MAX_STRIP_LENGTH)
    {
        // Halt; cannot recover from a pixel strip data array that cannot be properly initialized.
        _Error_Handler(__FILE__, __LINE__);
    }

    // Copy start frame data into strip update packet.
    for (int i = 0; i < APA102_START_FRAME_BYTES; i++)
    {
        APA102_Strip[i] = APA102_StartFrameByte;
    }


    // Copy end frame data into strip update packet.
    int j = sizeof(APA102_Strip);
    for (int i = 0; i < APA102_START_FRAME_BYTES; i++)
    {
        APA102_Strip[j] = APA102_EndFrameByte;
        j--;
    }


    // Initialize each pixel update frame to OFF
    for (int i = APA102_START_FRAME_BYTES; i < (APA102_STRIP_UPDATE_PACKET_BYTES - APA102_END_FRAME_BYTES); i+=APA102_START_FRAME_BYTES)
    {
        // First three bits must be HIGH, remaining five are a global pixel brightness that we'll default to max for the time being.
        APA102_Strip[i] = 0b11111111;
    }

    // Return Status
    return APA102_SUCCESS;
}


/*
 * APA102_SetPixel - Sets a single pixel to the prescribed color intensities.
 *  arguments: pixel number in strip (1 based), red intensity, green intensity, blue intensity
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_SetPixel(uint32_t pixel, uint8_t red, uint8_t grn, uint8_t blu)
{
    // Variable Declarations
    uint32_t position = 0;

    // Sanity check pixel number input
    if (pixel > APA102_STRIPLEN)
    {
        return APA102_FAILURE;
    }

    // Account for 0 based array
    pixel --;

    // Calculate desired pixel data's position in the strip array.
    position = (APA102_START_FRAME_BYTES + (pixel * APA102_BYTES_PER_PIXEL));

    // Insert desired pixel data into strip array.
    APA102_Strip[position + 1] = blu;
    APA102_Strip[position + 2] = grn;
    APA102_Strip[position + 3] = red;

    // Return Status
    return APA102_SUCCESS;
}


/*
 * APA102_SetStrip - Sets the entire strip to the prescribed color intensities.
 *  arguments: red intensity, green intensity, blue intensity
 *    returns: Status flag based on HAL status.  Failures are not considered
 *             show-stopping based on streaming nature of a typical implementation.
 */
APA102_result APA102_SetStrip(uint8_t red, uint8_t grn, uint8_t blu)
{
    // Update strip color, pixel by pixel.  TODO- Optimize this loop with some fancy schmancy DMA like magic?
    for (int i = 1; i <= APA102_STRIPLEN; i++)
    {
        APA102_SetPixel(i, red, grn, blu);
    }

    // Return Status
    return APA102_SUCCESS;
}


/*
 * APA102_Intensity_To_Current - Calculates channel current consumption based on specified intensity. Currently assumes
 *                         linear relationship between intensity and current draw. May be turned into a macro if
 *                         linear relationship assumption is kept long term.
 *  arguments: Intensity of a single pixel color (channel).
 *    returns: Calculated current needs of the given single pixel color (channel).
 */
uint8_t APA102_Intensity_To_Current(uint8_t channelIntensity)
{
    // TODO - Need to account for each pixel's quiescent current and take some measurements so something more accurate then an assumed linear relationship can be used for the scaling.

    // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return (channelIntensity - 0) * (APA102_CHANNEL_CURRENT - 0) / (255 - 0) + 0;
}
