#ifndef CMMB_API_H
#define CMMB_API_H


enum {
    CMMB_CA_CAT_TABLE = 0,
    CMMB_CA_EMM_INFO,
    CMMB_CA_ECM_INFO,
    CMMB_CA_ES_INFO,
    CMMB_CA_PROG_INFO
};

typedef struct ProgInfo_t {
    uint16_t serviceID;
    uint8_t  encrypted;
} ProgInfo;

typedef struct ECM_t {
    uint8_t transportType;
    uint8_t dataType;
} ECM;

typedef struct EMM_t {
    uint16_t serviceID;
    uint8_t  dataType;
    uint8_t  mfID;
    uint8_t  msfID;
} EMM;

typedef struct ElementaryStream_t {
    uint16_t  num;
    uint8_t   bVideo;
    uint8_t   bAudio;
    uint8_t   bData;
} ElementaryStream;


#endif /* CMMB_API_H */
