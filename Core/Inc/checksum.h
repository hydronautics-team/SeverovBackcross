
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#include <stdint.h>
#include <stdbool.h>

//bool IsChecksumm16bCorrect(uint8_t *msg, uint16_t length);
//void AddChecksumm16b(uint8_t *msg, uint16_t length);

bool IsChecksum8bCorrect(const uint8_t *msg, uint16_t length);
void AddChecksum8b(uint8_t *msg, uint16_t length);


#endif /* CHECKSUM_H_ */
