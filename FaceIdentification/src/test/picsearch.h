#ifndef _PICSEARCH_H_
#define _PICSEARCH_H_

//#define IMAGE_FEATURE_NUM 4096
//#define IMAGE_FEATURE_NUM 1000
#define IMAGE_FEATURE_NUM 2048
#define GDS_ID_LEN 32
#define STORE_ID_LEN 32
#define CATEGORY_ID_LEN 128
#define PIC_ID_LEN 32 + 1
#define PIC_MD5_LEN 32 + 1
#define URL_LEN 256
//20160822
#define FILE_NAME_LEN 128
#define GDS_NAME_LEN 256
#define TYPE_LEN 2+1
#define STATUS_LEN 1+1
#define CATEGORY_LEN 32
#define BRAND_LEN 32
/**
class stringhasher
{
    public:
        enum {
            bucket_size = 1,
            min_buckets = 400000
        };

        size_t operator()(const string &s)const
        {
            size_t h = 0;
            string::const_iterator p, p_end;
            for(p = s.begin(), p_end = s.end(); p != p_end; ++p)
            {
                h = 101 * h + (*p);
            }
            return h;
        }

        bool inline operator() (const string& s1, const string& s2) const
        {
            return s1 < s2;
        }
};
**/
#ifdef SPICIdx
#undef SPICIdx
struct SPICIdx{
     char chMD5[PIC_MD5_LEN];
     int  nNum;
};
#endif

struct SFeature{
     char chMD5[PIC_MD5_LEN];
     float fFeature[IMAGE_FEATURE_NUM];
};

struct SFeatureidx{
     size_t nPos;
     size_t nLen;
};
struct SGds{
     char chGdsId[GDS_ID_LEN];
     char chStoreId[STORE_ID_LEN];
     char chType[TYPE_LEN];
     char chStatus[STATUS_LEN];
     char chValidCity[STATUS_LEN];
     char chCategory[CATEGORY_LEN];
};
/**
struct SGdsList{
    char chGdsId[GDS_ID_LEN];
    char chStoreId[STORE_ID_LEN];
    char chStatus[STATUS_LEN];
};
**/
struct SGdsList{
    uint64_t uGdsId;
    uint64_t uStoreId;
    uint16_t uStatus;
    char chCategory[CATEGORY_LEN];
    SGdsList(){
        uGdsId=0;
        uStoreId=0;
        uStatus=0;
        memset(chCategory, 0, sizeof(chCategory));
    }
    friend bool operator < (const SGdsList&a, const SGdsList&b)
    {
        if(a.uGdsId != b.uGdsId)
        {
            return a.uGdsId < b.uGdsId;  //升序
        }
        else if(a.uStoreId != b.uStoreId)
        {
            return a.uStoreId < b.uStoreId;
        }
        else if(a.uStatus != b.uStatus)
        {
            return a.uStatus < b.uStatus;
        }
        else
        {
            return strcmp(a.chCategory, b.chCategory) < 0;
        }
    }
};
//
struct SGdsProded{
    uint64_t uGdsId;
    uint64_t uStoreId;
    uint16_t uStatus;
    SGdsProded(){
        uGdsId=0;
        uStoreId=0;
        uStatus=0;
    }
    friend bool operator < (const SGdsProded&a, const SGdsProded&b)
    {
        if(a.uGdsId != b.uGdsId)
        {
            return a.uGdsId < b.uGdsId;  //升序
        }
        else if(a.uStoreId != b.uStoreId)
        {
            return a.uStoreId < b.uStoreId;
        }
        else
        {
            return a.uStatus < b.uStatus;
        }
    }
};


struct SGdsInfo{
    uint64_t uGdsId;
    uint64_t uStoreId;
    SGdsInfo(){
        uGdsId=0;
        uStoreId=0;
    }
    friend bool operator < (const SGdsInfo&a, const SGdsInfo&b)
    {
        if(a.uGdsId != b.uGdsId)
        {
            return a.uGdsId < b.uGdsId;  //升序
        }
        else
        {
            return a.uStoreId < b.uStoreId;
        }
    }
};

struct STmpPicId{
    uint64_t uGdsId;
    uint64_t uStoreId;
    uint16_t uOrd;
    uint16_t uStatus;
    STmpPicId(){
        uGdsId=0;
        uStoreId=0;
        uOrd=0;
        uStatus=0;
    }
    friend bool operator < (const STmpPicId &a, const STmpPicId &b)
    {
        if(a.uGdsId != b.uGdsId)
        {
            return a.uGdsId < b.uGdsId;  //升序
        }
        else if(a.uStoreId != b.uStoreId)
        {
            return a.uStoreId < b.uStoreId;
        }
        else if(a.uOrd != b.uOrd)
        {
            return a.uOrd < b.uOrd;
        }
        else
        {
            return a.uStatus < b.uStatus;
        }
    }
};

struct SPicId{
    uint64_t uGdsId;
    uint64_t uStoreId;
    uint16_t uOrd;
    SPicId(){
        uGdsId=0;
        uStoreId=0;
        uOrd=0;
    }
    friend bool operator < (const SPicId&a, const SPicId&b) 
    {
        if(a.uGdsId != b.uGdsId)
        {
            return a.uGdsId < b.uGdsId;  //升序
        }
        else if(a.uStoreId != b.uStoreId)
        {
            return a.uStoreId < b.uStoreId;
        }
        else
        {
            return a.uOrd < b.uOrd;
        }
    }
};

struct SImgTable{
    char chGdsId[GDS_ID_LEN];
    char chUrl[URL_LEN];
    char chMD5[PIC_MD5_LEN];
    char chIdxUrl[PIC_MD5_LEN];
    int nStatus;
};

struct SWordGds{
    char chGdsId[GDS_ID_LEN];
    char chStoreId[STORE_ID_LEN];
    char chName[GDS_NAME_LEN];
    char chType[TYPE_LEN];
    char chStatus[STATUS_LEN];
    char chValidCity[STATUS_LEN];
};

struct SWordGdsList{
    char chGdsId[GDS_ID_LEN];
    char chStoreId[STORE_ID_LEN];
    char chName[GDS_NAME_LEN];
};

#endif
