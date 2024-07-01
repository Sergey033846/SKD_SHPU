#ifndef objectsCPP
#define objectsCPP

#include <vcl.h>
#include <math.h>
#include <stdio.h>

#include <io.h>
#include <fcntl.h>

#define MAX_STVOL 5
#define MAX_RUDNIK 2
#define MAX_YEAR 10
#define START_YEAR 2005

enum TChannelType {tchtDISKRET,tchtANALOG,tchtCOUNTER,tchtPROGRAM,tchtCONTROL,tchtRESERVED};
enum TDimensionType {tdtNONE,tdtON,tdtOFF,tdtU,tdtI,tdtP,tdtSPEED};
enum TDimensionKind {tdkNONE,tdkV,tdkmV,tdkA,tdkmA,tdkVatt,tdkkVatt};

enum TArcFileState {tafsCURRENT,tafsACTUAL,tafsDOWNLOADED,tafsNOT_DOWNLOADED};
enum TShedAction {tsaGET_ACTUAL,tsaGET_ACTUAL_STAT,tsaGET_NOT_DOWNLOADED};

enum TCOMPortID {tcpCOM1,tcpCOM2,tcpCOM3,tcpCOM4};
enum TDialMode {tdmTONE,tdmPULSE};

enum T_BALANS_TYPE {tbtSMENA,tbtDAY,tbtMONTH,tbtQUARTER,tbtHALFYEAR,tbtYEAR,tbtSTVOL,tbtRUDNIK};

class TChannel;
struct TChannelData;
class TArchive;
class TArchiveRecord;
struct TLogPoint;
struct TCiklPod;
struct TLoginRecord;

struct TWarning;

struct TArcInfo;
struct TShedRecord;

struct TComModemConfig;

struct TArcStat;
struct TTimeStat;
struct T7Record;

struct T_DISKRET_TBI;
struct T_UNIO_TBI;

void Stat2TimeStat(TArcStat *st,TTimeStat *tst);

template <class T> class TVariantList;

typedef TVariantList <int> TIntList;
typedef TVariantList <TWarning> TWarningList;
typedef TVariantList <TChannel> TChannelList;
typedef TVariantList <TArcStat> TArcStatList;
typedef TVariantList <TTimeStat> TTimeStatList;
typedef TVariantList <TChannelData> TChannelDataList;
typedef TVariantList <TArchive> TArchiveList;

typedef TVariantList <TLogPoint> TLogPointList;
typedef TVariantList <TCiklPod> TCiklPodList;

typedef TVariantList <T7Record> T7List;

typedef TVariantList <TArchiveRecord> TArcRecList;

typedef TVariantList <TLoginRecord> TLogRecList;
typedef TVariantList <TArcInfo> TArcInfoList;
typedef TVariantList <TShedRecord> TShedRecordList;

//------------------------------------------------------------------------------
// функция округления
double round(double x)
{
        double y = x;

        double dx = x - int(x);
        if (dx < 0.5) y = int(x);
        else y = int(x)+1;

        return y;
}
//----------------------------------------------------------------------
// настройки модемов и COM-портов
struct TComModemConfig
{
        TCOMPortID COM_PORT_ID; // id COM-порта 0-COM1,1-COM2 и т.д.
        TDialMode DIAL_MODE;
};
//----------------------------------------------------------------------

struct T_DISKRET_TBI
{
        bool _1;
        bool _2;
        bool _3;
        bool _4;
};

struct T_UNIO_TBI
{
        short _1stTBI,_2ndTBI;
        short COUNTERS;
};
//----------------------------------------------------------------------

class TSysParams
{
public:
        AnsiString FileName;

        int RudNameIndex;
        int StvolNameIndex;

        long RefrTime;
        long ArcTime;

        char DayTime1;
        char DayTime2;
        char NightTime1;
        char NightTime2;

        char ArcDir[50];
        char SysDir[50];
        char MediaDir[50];

        // отчет за смену
        TColor repRGcol;  char repRGlinestyle;
        TColor repRLcol;  char repRLlinestyle;
        TColor repRRcol;  char repRRlinestyle;
        TColor repROcol;  char repROlinestyle;
        TColor repDIAGcol;
        //---------------

        // диаграмма скорости
        TColor wcolor; // рабочая
        TColor scolor; // сигнальная
        TColor zcolor; // защитная
        TColor fcolor; // фактическая
        TColor bkcolor;// фон
        //-------------------

        //-------------------
        TComModemConfig comm;
        //-------------------

        //-------------------
        short dt_peresm;       // dt пересменки в минутах
        //-------------------

        char RARArcDir[50];
        char FlashDir[50];

        TColor repPCcol;  char repPClinestyle;

        TSysParams(AnsiString f_name);
        int Save();
        int Load();
};

TSysParams::TSysParams(AnsiString f_name)
{
        FileName = f_name;

        RudNameIndex = StvolNameIndex = 0;

        RefrTime = 200;
        ArcTime = 500;

        DayTime1 = 8;
        DayTime2 = 20;
        NightTime1 = 20;
        NightTime2 = 8;

        strcpy(ArcDir,"");
        strcpy(SysDir,"");
        strcpy(MediaDir,"");
};

int TSysParams::Save()
{
        FILE *f;

        int err;

        f = fopen(FileName.c_str(),"wb");

        if (f != NULL)
        {
                fwrite(&RudNameIndex,sizeof(int),1,f);
                fwrite(&StvolNameIndex,sizeof(int),1,f);

                fwrite(&RefrTime,sizeof(long),1,f);
                fwrite(&ArcTime,sizeof(long),1,f);

                fwrite(&DayTime1,1,1,f);
                fwrite(&DayTime2,1,1,f);
                fwrite(&NightTime1,1,1,f);
                fwrite(&NightTime2,1,1,f);

                fwrite(&ArcDir,1,50,f);
                fwrite(&SysDir,1,50,f);
                fwrite(&MediaDir,1,50,f);

                fwrite(&repRGcol,sizeof(TColor),1,f);
                fwrite(&repRGlinestyle,1,1,f);
                fwrite(&repRLcol,sizeof(TColor),1,f);
                fwrite(&repRLlinestyle,1,1,f);
                fwrite(&repRRcol,sizeof(TColor),1,f);
                fwrite(&repRRlinestyle,1,1,f);
                fwrite(&repROcol,sizeof(TColor),1,f);
                fwrite(&repROlinestyle,1,1,f);
                fwrite(&repDIAGcol,sizeof(TColor),1,f);

                fwrite(&wcolor,sizeof(TColor),1,f);
                fwrite(&scolor,sizeof(TColor),1,f);
                fwrite(&zcolor,sizeof(TColor),1,f);
                fwrite(&fcolor,sizeof(TColor),1,f);
                fwrite(&bkcolor,sizeof(TColor),1,f);

                fwrite(&comm,sizeof(TComModemConfig),1,f);

                fwrite(&dt_peresm,sizeof(short),1,f);

                fwrite(&RARArcDir,1,50,f);
                fwrite(&FlashDir,1,50,f);

                fwrite(&repPCcol,sizeof(TColor),1,f);
                fwrite(&repPClinestyle,1,1,f);
        }
        else return -1;

        fclose(f);
        return 0;
};

int TSysParams::Load()
{
        FILE *f;

        f = fopen(FileName.c_str(),"rb");

        if (f != NULL)
        {
                fread(&RudNameIndex,sizeof(int),1,f);
                fread(&StvolNameIndex,sizeof(int),1,f);

                fread(&RefrTime,sizeof(long),1,f);
                fread(&ArcTime,sizeof(long),1,f);

                fread(&DayTime1,1,1,f);
                fread(&DayTime2,1,1,f);
                fread(&NightTime1,1,1,f);
                fread(&NightTime2,1,1,f);

                fread(&ArcDir,1,50,f);
                fread(&SysDir,1,50,f);
                fread(&MediaDir,1,50,f);

                fread(&repRGcol,sizeof(TColor),1,f);
                fread(&repRGlinestyle,1,1,f);
                fread(&repRLcol,sizeof(TColor),1,f);
                fread(&repRLlinestyle,1,1,f);
                fread(&repRRcol,sizeof(TColor),1,f);
                fread(&repRRlinestyle,1,1,f);
                fread(&repROcol,sizeof(TColor),1,f);
                fread(&repROlinestyle,1,1,f);
                fread(&repDIAGcol,sizeof(TColor),1,f);

                fread(&wcolor,sizeof(TColor),1,f);
                fread(&scolor,sizeof(TColor),1,f);
                fread(&zcolor,sizeof(TColor),1,f);
                fread(&fcolor,sizeof(TColor),1,f);
                fread(&bkcolor,sizeof(TColor),1,f);

                fread(&comm,sizeof(TComModemConfig),1,f);

                fread(&dt_peresm,sizeof(short),1,f);

                fread(&RARArcDir,1,50,f);
                fread(&FlashDir,1,50,f);

                fread(&repPCcol,sizeof(TColor),1,f);
                fread(&repPClinestyle,1,1,f);
        }
        else return -1;

        fclose(f);
        return 0;
};

//------------------------------------------------------------------------------
struct tmodeKoef
{
        float Vmax;

        float a_zam;
        float a_razg;
        float a_oth;

        float L_zam;
        float L_razg;
        float L_oth;
        float L_dot;

        float V_low;      // отклонение сигнальной скорости в % в диапазоне разгона и торможения
        float V_hi;       // отклонение защитной скорости в % в диапазоне разгона и торможения
        float dV_low;      // отклонение сигнальной скорости в % в диапазоне отхода и дотяжки
        float dV_hi;       // отклонение защитной скорости в % в диапазоне отхода и дотяжки

        float dL_razg;
        float dL_zam;

        float dV_razg;
        float dV_zam;
};

struct tsysKoef
{
        tmodeKoef mode_koefs[4];  // параметры режимов

        float L_MAX;     // высота ствола
        float V_koef_U;  // коэффициент пересчета скорости через Uст
        float VH_koef_DPI;  // коэффициент пересчета скорости и высоты через ДПИ

        //--------резерв
        float dH_ned;       // dH недоподъема иди переподъема
        char reserved[4];
        //----------------------------------

        float hpp_0;
        float h0_1;
        float h1_2;
        float h2_3;
        float h3_4;
        float h4_5;

        char reserved2[200]; // резерв
};

class TSysKoef
{
public:
        tsysKoef koef;

        void Load();
        void Save();
};

void TSysKoef::Save()
{
        FILE *f = fopen("sys_koef.ini","wb");

        fwrite(&koef,sizeof(tsysKoef),1,f);

        // формирование резерва
/*        char temp=0;
        fwrite(&temp,1,256,f);*/

        fclose(f);
}

void TSysKoef::Load()
{
        FILE *f = fopen("sys_koef.ini","rb");

        if (f != NULL)
        {
                fread(&koef,sizeof(tsysKoef),1,f);
                fclose(f);
        }        
}
//------------------------------------------------------------------------------

// дескриптор канала
struct TChannel
{
public:
        int ChannelID;
        char ChannelCaption[30]; // дисп. наим.
        TChannelType ChannelType;
        TDimensionType Dimension;
        TDimensionKind DimensionKind;
        float MIN_DIM;
        float MAX_DIM;

        bool is_visible;         // ???
        TColor col;

        int NFPGA;
        int n_channel;

        // линейное преобразование
        float a;
        float b;
        float k;

        // цена импульса
        float imp;

        TColor col_nact;

        //--------коэффициент трансформации
        float k_trans;
        //----------------------------------

        char reserved[40];  // резерв
};

//------------------------------------------------------------------------------

// класс - однонаправленный список
template <class T>
struct TLRecord
{
        T *data;
        TLRecord <T>* next;
};

template <class T>
class TVariantList
{
public:
        TLRecord <T>* head;
        TLRecord <T>* tail;

        int count;

        TVariantList();
        ~TVariantList();

        void DestroyList();

        T* operator[] (int i); // первый элемент - № 0
        void Add(T* new_data); // добавление в конец списка
        void Del(int i);       // удаление i-го элемента

        int WriteToFile(AnsiString FileName);

        // без открытия и закрытия файла,
        // count не пишет
        int WriteToFile2(FILE *f);

        int AppendToFile(AnsiString FileName,T* rec);

        int ReadFromFile(AnsiString FileName);
        int ReadFromFile2(FILE *f);

        T* LoadItem(AnsiString FileName,int k); // 1-ая запись при k = 0

        int GetLastID(); //?
};

template <class T>
int TVariantList <T>::GetLastID()
{
        if (count != 0) return tail->data->ChannelID;
        else return -1;
}

template <class T>
void TVariantList <T>::Add(T* new_data)
{
        TLRecord <T> *temp = new TLRecord <T>;
        temp->next = NULL;
        temp->data = new_data;
        if (!tail) {
                head = tail = temp;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
        count++;
}

template <class T>
TVariantList <T>::TVariantList()
{
        count = 0;
        head = NULL;
        tail = NULL;
}

template <class T>
void TVariantList <T>::DestroyList()
{
        while (head)
        {
                Del(0);
        }
        head = tail = NULL;
        count = 0;
}

template <class T>
TVariantList <T>::~TVariantList()
{
//        DestroyList(); 
}

template <class T>
T* TVariantList <T>::operator[] (int i)
{
    if (i < count)
    {
        TLRecord <T> *temp = head;

        for (int j=0; j<i; j++)
        {
                temp = temp->next;
        }
        return temp->data;
    }
    else return NULL;
}

template <class T>
void TVariantList <T>::Del(int i)
{
        TLRecord <T> *temp = head;
        TLRecord <T> *prev = NULL;
        for (int j=0; (j<i) && (temp!=NULL); j++)
        {
                prev = temp;
                temp = temp->next;
        }
        if (temp != NULL)
        {
                if (prev != NULL)
                {
                        prev->next = temp->next;
                }

                if (temp==tail)
                {
                        tail = prev;
                }

                if (temp==head)
                {
                        head = temp->next;
                }

                delete temp->data;
                delete temp;
                count--;
        }
}

template <class T>
T* TVariantList <T>::LoadItem(AnsiString FileName,int k)
{
        T* rec;

        FILE *f;

        f = fopen(FileName.c_str(),"rb");

        if (f != NULL)
        {
                fseek(f,sizeof(int)+k*sizeof(T),SEEK_SET);
                fseek(f,k*sizeof(T),SEEK_SET);
                fread(rec,sizeof(T),1,f);
        }
        else return NULL;

        fclose(f);
        return rec;
}

template <class T>
int TVariantList <T>::AppendToFile(AnsiString FileName,T* rec)
{
        FILE *f;

        f = fopen(FileName.c_str(),"ab");

        if (f != NULL)
        {
                fseek(f,0,SEEK_SET);
                fwrite(&count,sizeof(int),1,f);
                fseek(f,0,SEEK_END);
                fwrite(rec,sizeof(T),1,f);
        }
        else return -1;

        fclose(f);
        return 0;
}

template <class T>
int TVariantList <T>::WriteToFile2(FILE *f)
{
        if (f != NULL)
        {
                for (int i=0; i<count; i++)
                {
                        fwrite((*this)[i],sizeof(T),1,f);
                }
        }
        else return -1;

        return 0;
}

template <class T>
int TVariantList <T>::WriteToFile(AnsiString FileName)
{
        FILE *f;

        f = fopen(FileName.c_str(),"wb");

        if (f != NULL)
        {
                fwrite(&count,sizeof(int),1,f);
                for (int i=0; i<count; i++)
                {
                        fwrite((*this)[i],sizeof(T),1,f);
                }
        }
        else return -1;

        fclose(f);
        return 0;
}

template <class T>
int TVariantList <T>::ReadFromFile(AnsiString FileName)
{
        FILE *f;

        f = fopen(FileName.c_str(),"rb");

        if (f != NULL)
        {
                int c;
                fread(&c,sizeof(int),1,f);
                for (int i=0; i<c; i++)
                {
                        T *temp = new T;
                        fread(temp,sizeof(T),1,f);
                        Add(temp);
                }
        }
        else return -1;

        fclose(f);
        return 0;
}

template <class T>
int TVariantList <T>::ReadFromFile2(FILE *f)
{
        if (f != NULL)
        {
                int c;
                fread(&c,sizeof(int),1,f);
                for (int i=0; i<c; i++)
                {
                        T *temp = new T;
                        fread(temp,sizeof(T),1,f);
                        Add(temp);
                }
        }
        else return -1;

        return 0;
}

//------------------------------------------------------------------------------

int GetChannelCount(TChannelList *ch_list,TChannelType ch_type)
{
        if (ch_list)
        {
                int c = 0;
                for (int i=0; i<ch_list->count; i++)
                {
                        if ((*ch_list)[i]->ChannelType == ch_type)
                        {
                                c++;
                        }
                }
                return c;
        }
        return 0;
};

// состояние канала
struct TChannelData
{
        int ChannelID;

        float analog;
        bool diskret;
        Word counter;

        short adc;      // отсчеты АЦП
};

TChannelData* GetElemByID(TChannelDataList* list,int ID)
{
        TLRecord <TChannelData>* temp = list->head;
        while (temp)
        {
            if (temp->data->ChannelID == ID) return temp->data;
            else temp = temp->next;
        }
        return NULL;
}

TChannel* GetChannelByNameAndDimension(TChannelList* list,char fcaption[30],TDimensionType dim)
{
        for (int i=0; i<list->count; i++)
        {
                if ((strcmp(fcaption,(*list)[i]->ChannelCaption) == 0) &&
                    dim == (*list)[i]->Dimension)
                {
                        return (*list)[i];
                }
        }
        return NULL;
}

// текущее состояние всех каналов,
// является разделяемым ресурсом

class TArchiveRecord
{
public:
        TDateTime date_time;
        TVariantList <TChannelData> *ChannelDataList;

        TArchiveRecord();
        ~TArchiveRecord();
};

TArchiveRecord::TArchiveRecord()
{
        ChannelDataList = new TVariantList <TChannelData>;
}

TArchiveRecord::~TArchiveRecord()
{
        delete ChannelDataList;
        ChannelDataList = NULL;
}

//------------------------------------------------------------------------------

struct TArcStat
{
        TDateTime date_time;

        short RudNameIndex;
        short StvolNameIndex;

        char MashinistName[20];
        char MasterName[20];

        char smena_id;

        short RTP_count;
        short RPM_count;
        short CP_count;
        float Total_L_count;
        float P;
        short Gruz3;
        short Gruz5;
        float mh;
};

// событие (тревога)
struct TWarning
{
        TDateTime date_time;
        unsigned long warning_id;
};

// архив-"файл"
class TArchive
{
public:
        AnsiString f_name;

        //--------------------
        TArcStat arc_stat;

        int count_arch_rec;

        //--------------------

        TArchive(TSysParams *sp,TChannelList *ch_list,AnsiString FileName,int id_oper);
        ~TArchive();

        int AppendToFile(TArchiveRecord* rec,TChannelList *ch_list);
        TArchiveRecord* LoadItem(TChannelList *ch_list,int k); // 1-ая запись при k = 0

        void WriteStat();
        void ReadStat(TArcStat *st);

        void ReadHeader(TChannelList *ch_list);

        void WriteWarnings(TWarningList *war_list);
        void ReadWarnings(TWarningList *war_list);
};

void TArchive::WriteWarnings(TWarningList *war_list)
{
        AnsiString w_name = f_name+".war";
        FILE *f = fopen(w_name.c_str(),"ab");
        for (int i = 0; i<war_list->count; i++) fwrite((*war_list)[i],sizeof(TWarning),1,f);
        fclose(f);
}

void TArchive::ReadWarnings(TWarningList *war_list)
{
        AnsiString w_name = f_name+".war";
        FILE *f = fopen(w_name.c_str(),"rb");
        TWarning *temp;
        TWarning tw;
        while (f!=NULL && feof(f) == 0)
        {
                if (fread(&tw,sizeof(TWarning),1,f) == 1)
                {
                        temp = new TWarning;
                        temp->date_time = tw.date_time;
                        temp->warning_id = tw.warning_id;
                        war_list->Add(temp);
                }
        }
        fclose(f);
}

void TArchive::ReadHeader(TChannelList *ch_list)
{
        AnsiString FileName = f_name+".arc";

        long fsize;

        int handle = open(FileName.c_str(),O_CREAT);
        fsize = filelength(handle);
        close(handle);

        long n_beg = 0;//sizeof(int);
        long nk = sizeof(TDateTime)+2*sizeof(long)+
                  (GetChannelCount(ch_list,tchtANALOG)-2)*sizeof(float)+
                  (GetChannelCount(ch_list,tchtCOUNTER)-1)*sizeof(float)+
                  (GetChannelCount(ch_list,tchtPROGRAM)-5)*sizeof(float);

        count_arch_rec = (fsize-n_beg)/nk;
}

void TArchive::ReadStat(TArcStat *st)
{
        AnsiString s_name = f_name+".sta";
        FILE *f = fopen(s_name.c_str(),"rb");
        if (f != NULL) fread(st,sizeof(TArcStat),1,f);
        fclose(f);
}

void TArchive::WriteStat()
{
        AnsiString s_name = f_name+".sta";
        FILE *f = fopen(s_name.c_str(),"wb");
        fwrite(&arc_stat,sizeof(TArcStat),1,f);
        fclose(f);
}

TArchive::~TArchive()
{
}

// id_oper == 0, то перезаписать файл,
// id_oper == 1, читать заголовок,
// id_oper == 2, добавлять в существующий
TArchive::TArchive(TSysParams *sp,TChannelList *ch_list,AnsiString FName,int id_oper)
{
        strcpy(arc_stat.MashinistName,"");
        strcpy(arc_stat.MasterName,"");
//------------------------------
        f_name = FName;

        AnsiString FileName = f_name+".arc";

        if (id_oper == 1)
        {
             FILE *f;
             f = fopen(FileName.c_str(),"rb");
             if (f != NULL)
             {
                long fsize;

                int handle = open(FileName.c_str(),O_CREAT);
                fsize = filelength(handle);
                close(handle);

                long n_beg = 0;//sizeof(int);
                long nk = sizeof(TDateTime)+2*sizeof(long)+
                          GetChannelCount(ch_list,tchtANALOG)*sizeof(float)+
                          GetChannelCount(ch_list,tchtCOUNTER)*sizeof(float)+
                          GetChannelCount(ch_list,tchtPROGRAM)*sizeof(float);

                count_arch_rec = (fsize-n_beg)/nk;
                fclose(f);
             }
             else count_arch_rec = 0;
        }
}

// для корректного выполнения данной функции необходимо,
// чтобы кол-во дискретных каналов было <= 64 (2 FPGA)
int TArchive::AppendToFile(TArchiveRecord* rec,TChannelList *ch_list)
{
        long l1 = 0,l2 = 0;
        short c1 = 0,c2 = 0;

                for (int i=0; i<ch_list->count; i++)
                {
                        if ((*ch_list)[i]->ChannelType == tchtDISKRET)
                        {
                                if (c1 < 32)
                                {
                                        long data = (*rec->ChannelDataList)[i]->diskret;
                                        data <<= c1;
                                        l1 += data;
                                        c1++;
                                }
                                else
                                {
                                        long data = (*rec->ChannelDataList)[i]->diskret;
                                        data <<= c2;
                                        l2 += data;
                                        c2++;
                                }
                        }
                }

        FILE *f;

        AnsiString FileName = f_name+".arc";

        f = fopen(FileName.c_str(),"ab");
        if (f != NULL)
        {
                fwrite(&rec->date_time,sizeof(TDateTime),1,f);
                fwrite(&l1,sizeof(long),1,f);
                fwrite(&l2,sizeof(long),1,f);
                for (int i=0; i<ch_list->count; i++)
                {
                        if ((*ch_list)[i]->ChannelType != tchtDISKRET)
                        {
                            if ((*ch_list)[i]->ChannelID < 35)
                                fwrite(&(*rec->ChannelDataList)[i]->analog,sizeof(float),1,f);
                        }
                }
        }
        else return -1;

        fclose(f);
        return 0;
};

TArchiveRecord* TArchive::LoadItem(TChannelList *ch_list,int k)
{
        TArchiveRecord *rec = new TArchiveRecord();

        FILE *f;

        AnsiString FileName = f_name+".arc";
        f = fopen(FileName.c_str(),"rb");

        if (f != NULL)
        {
                int n_beg = 0;
//                int n_beg = sizeof(int);
                int nk = sizeof(TDateTime)+2*sizeof(long)+
                         (GetChannelCount(ch_list,tchtANALOG)-2)*sizeof(float)+
                         (GetChannelCount(ch_list,tchtCOUNTER)-1)*sizeof(float)+
                         (GetChannelCount(ch_list,tchtPROGRAM)-5)*sizeof(float);
                fseek(f,n_beg+k*nk,SEEK_SET); //переместиться на нужную запись

                fread(&rec->date_time,sizeof(TDateTime),1,f);
                long l1,l2;
                fread(&l1,sizeof(long),1,f);
                fread(&l2,sizeof(long),1,f);

                TChannelData *ch_data;
                short c1 = 0,c2 = 0;
                long mask,data;
                for (int i=0; i<ch_list->count; i++)
                {
                        ch_data = new TChannelData();

                        if ((*ch_list)[i]->ChannelType == tchtDISKRET)
                        {
                                mask = 1;
                                if (c1 < 32)
                                {
                                        mask <<= c1;
                                        data = l1 & mask;
                                        ch_data->diskret = data>0;
                                        c1++;
                                }
                                else
                                {
                                        mask <<= c2;
                                        data = l2 & mask;
                                        ch_data->diskret = data>0;
                                        c2++;                                
                                }
                        }
                        else
                        if ((*ch_list)[i]->ChannelID<35)
                        {
                                fread(&(ch_data->analog),sizeof(float),1,f);
                        }

                        rec->ChannelDataList->Add(ch_data);
                }
        }
        else return NULL;

        fclose(f);
        return rec;
};

//------------------------------------------------------------------------------
// класс-"система координат"
//------------------------------------------------------------------------------
struct TLogPoint
{
        float x;
        float y;
};

struct T7Record
{
        TLogPoint lp;
        char n;
};

// физические коэффициенты логической единицы
struct TKoordKoef
{
        int kx;
        int ky;
};

class TKoordSystem
{
public:
//        TImage *img;

        TImage* par_img;

        Graphics::TBitmap *btmp;
        TRect r;

        TLogPoint log_koord; // логическое начало координат
        TPoint koord;        // физическое  начало координат в пикселях

        float max_gr_x;
        float max_gr_y;

        TColor col;

        TKoordKoef koef;

        int log_x;
        int log_y;

        bool draw_setka;
        bool draw_numbers_y;
        bool draw_numbers_x;
        bool draw_kslines;

        TColor bk_col;       // цвет координатной плоскости
        TColor text_col;     // цвет текста (цифр)

        TKoordSystem(TImage* par_img,TRect rect,TPoint k,int lx,int ly);
        ~TKoordSystem();

        void DrawKoord();

        void DrawLine(TLogPoint *p, TLogPoint *val, TColor col, int line_thickness, short style);
        void DrawPoint(TLogPoint *val,TColor col);
        void Draw7Point(T7Record *_7rec,TColor txtcol);
        void DrawNodeValue(TImage *p_img,TLogPoint *val,TColor col);

        void UpdateKoords();
        void DrawKoordSystem();

        void Redraw();
};

void TKoordSystem::Redraw()
{
        TRect RectS;
        RectS = Rect(0,0,r.Width(),r.Height());
        par_img->Canvas->CopyRect(r,btmp->Canvas,RectS);
}

void TKoordSystem::UpdateKoords()
{
        int max_x = r.Width();
        int max_y = r.Height();
        
        int xx = 1000/log_x;
        int yy = 50/log_y;     //переделать

        int ix = max_x/koef.kx;
        int iy = max_y/koef.ky;

        btmp->Canvas->Font->Color = clWhite;

        btmp->Canvas->Pen->Color = clGray;
        btmp->Canvas->Pen->Style = psDot;
        for (int i=1; i<ix; i++)
        {
                btmp->Canvas->Rectangle(koord.x+i*xx*koef.kx,0,koord.x+i*xx*koef.kx+1,max_y);
                btmp->Canvas->TextOutA(koord.x+i*xx*koef.kx-3,koord.y-18,IntToStr(i*log_x));
        }
/*        for (int j = 1; j<iy/2+1; j++)
        {
                img->Canvas->Rectangle(0,koord.y+j*yy*koef.ky,img->ClientWidth,koord.y+j*yy*koef.ky+1);
                img->Canvas->Rectangle(0,koord.y-j*yy*koef.ky,img->ClientWidth,koord.y-j*yy*koef.ky+1);

//                img->Canvas->TextOutA(3,koord.y+j*yy*koef.ky-3,IntToStr(-j*50));  //!!!!!
                img->Canvas->TextOutA(3,koord.y-j*yy*koef.ky-3,IntToStr(j*50));
        }*/

        for (int j = 1; j<iy+1; j++)
        {
//                img->Canvas->Rectangle(0,koord.y+j*yy*koef.ky,img->ClientWidth,koord.y+j*yy*koef.ky+1);
                btmp->Canvas->Rectangle(0,koord.y-j*yy*koef.ky,max_x,koord.y-j*yy*koef.ky+1);

//                img->Canvas->TextOutA(3,koord.y+j*yy*koef.ky-3,IntToStr(-j*50));  //!!!!!
                btmp->Canvas->TextOutA(3,koord.y-j*yy*koef.ky-3,IntToStr(j*log_y));
        }

        btmp->Canvas->Pen->Style = psSolid;
        btmp->Canvas->Pen->Color = clGray;
        btmp->Canvas->Rectangle(koord.x,koord.y-1,koord.x+max_x,koord.y+1);
        btmp->Canvas->Rectangle(koord.x-1,0,koord.x+1,max_y);
        btmp->Canvas->MoveTo(koord.x,koord.y);
};

void TKoordSystem::DrawLine(TLogPoint *p1, TLogPoint *val, TColor col, int line_thickness, short style)
{
        int x1,y1,x2,y2;
        x1 = koord.x+(p1->x-log_koord.x)/log_x*koef.kx;
        y1 = koord.y-(p1->y-log_koord.y)/log_y*koef.ky;
        x2 = koord.x+(val->x-log_koord.x)/log_x*koef.kx;
        y2 = koord.y-(val->y-log_koord.y)/log_y*koef.ky;

        btmp->Canvas->MoveTo(x1,y1);
        btmp->Canvas->Pen->Color = col;
        btmp->Canvas->Pen->Width = line_thickness;
        btmp->Canvas->Pen->Style = (TPenStyle)style;
        btmp->Canvas->LineTo(x2,y2);
        btmp->Canvas->Pen->Width = 1;
        btmp->Canvas->Pen->Style = psSolid;
}

void TKoordSystem::DrawPoint(TLogPoint *val,TColor col)
{
        int x,y;
        x = koord.x+(val->x-log_koord.x)/log_x*koef.kx;
        y = koord.y-(val->y-log_koord.y)/log_y*koef.ky;

        btmp->Canvas->Pen->Color = col;
        btmp->Canvas->Brush->Color = col;
        btmp->Canvas->Ellipse(x-3,y-3,x+3,y+3);
}

void TKoordSystem::Draw7Point(T7Record *_7rec,TColor txtcol)
{
        int x,y;
        TLogPoint *val = &(_7rec->lp);
        x = koord.x+(val->x-log_koord.x)/log_x*koef.kx;
        y = koord.y-(val->y-log_koord.y)/log_y*koef.ky;

        btmp->Canvas->Font->Color = txtcol;
        btmp->Canvas->Font->Name = "Arial";
        btmp->Canvas->Font->Size = 8;
        btmp->Canvas->Font->Style = TFontStyles()<< fsBold;
        btmp->Canvas->Brush->Color = clWhite;
        btmp->Canvas->TextOutA(x,y,_7rec->n);
}

void TKoordSystem::DrawNodeValue(TImage *p_img,TLogPoint *val,TColor col)
{
        int x,y;

        x = koord.x+(val->x-log_koord.x)/log_x*koef.kx;
        y = koord.y-(val->y-log_koord.y)/log_y*koef.ky;

        if (val->x >= log_koord.x && val->x <= max_gr_x &&
            val->y >= log_koord.y && val->y <= max_gr_y)
        {
                p_img->Left = x-4;
                p_img->Top = y-4;
                p_img->Visible = true;
        }
}

/*void TKoordSystem::DrawValue(TLogPoint val,TColor col)
{
        Word hour,min,sec,msec;
        DecodeTime(val.x,hour,min,sec,msec);
        long val_total_msec = long(msec)+long(sec)*1000+long(min)*60*1000+long(hour)*3600*1000;

        Word hour2,min2,sec2,msec2;
        DecodeTime(log_koord.x,hour2,min2,sec2,msec2);
        long logkoord_total_msec = long(msec2)+long(sec2)*1000+long(min2)*60*1000+long(hour2)*3600*1000;

        long x,y;

        long dx = val_total_msec-logkoord_total_msec;

        x = koord.x+dx/log_x*koef.kx;
        y = koord.y-long(val.y/log_y*koef.ky);

        img->Canvas->Lock();
        img->Canvas->Pen->Color = col;
        img->Canvas->Pen->Width = 2;
        img->Canvas->LineTo(x,y);
        img->Canvas->Brush->Color = col;
        img->Canvas->Ellipse(x-3,y-3,x+3,y+3);
        img->Canvas->Unlock();
};*/

void TKoordSystem::DrawKoord()
{
        int max_x = r.Width();
        int max_y = r.Height();

        btmp->Canvas->Pen->Color = clGray;
        btmp->Canvas->Pen->Style = psDot;
        int ix = max_x/koef.kx;
        int iy = max_y/koef.ky;

        for (int i = 0; i<ix; i++)
        {
                btmp->Canvas->Rectangle(koord.x+i*koef.kx,0,koord.x+i*koef.kx+1,max_y);
        }
/*        for (int j = 0; j<iy/2+1; j++)
        {
                img->Canvas->Rectangle(0,koord.y+j*koef.ky,img->ClientWidth,koord.y+j*koef.ky+1);
                img->Canvas->Rectangle(0,koord.y-j*koef.ky,img->ClientWidth,koord.y-j*koef.ky+1);
        }*/
        for (int j = 0; j<iy+1; j++)
        {
                btmp->Canvas->Rectangle(0,koord.y-j*koef.ky,max_x,koord.y-j*koef.ky+1);
        }

        btmp->Canvas->Pen->Style = psSolid;
        btmp->Canvas->Pen->Color = clGray;
        btmp->Canvas->Rectangle(koord.x,koord.y-1,koord.x+max_x,koord.y+1);
        btmp->Canvas->Rectangle(koord.x-1,0,koord.x+1,max_y);
};

TKoordSystem::TKoordSystem(TImage* p_img,TRect rect,TPoint k,int lx,int ly)
{
        draw_setka = true;
        draw_numbers_y = true;
        draw_numbers_x = true;
        draw_kslines = true;

        bk_col = clBlack;
        text_col = clWhite;

        log_x = lx;
        log_y = ly;

        par_img = p_img;
        r = rect;
        btmp = new Graphics::TBitmap;
        btmp->Width = r.Width();
        btmp->Height = r.Height();

        koord.x = k.x;
        koord.y = k.y;

        col = clBlack;

        koef.kx = 35;
        koef.ky = 35;

        btmp->Canvas->MoveTo(k.x,k.y);
};

TKoordSystem::~TKoordSystem()
{
        delete btmp;
};

void TKoordSystem::DrawKoordSystem()
{
        float ldx = (log_koord.x-int(log_koord.x));
        int kdx = round(ldx * koef.kx / log_x);

        btmp->Canvas->Brush->Color = bk_col;
        TRect RectS;
        RectS = Rect(0,0,r.Width(),r.Height());
        btmp->Canvas->FillRect(RectS);

        int max_x = r.Width();
        int max_y = r.Height();

        int ix = max_x/koef.kx;
        int iy = max_y/koef.ky;

        max_gr_x = log_koord.x+ix+1;
        max_gr_y = log_koord.y+iy+1;

        btmp->Canvas->Font->Color = text_col;

        btmp->Canvas->Pen->Color = clGray;
        btmp->Canvas->Pen->Style = psDot;
        for (int i=0; i<ix+1+1; i++)
        {
                if (draw_setka) btmp->Canvas->Rectangle(-kdx+ koord.x+i*koef.kx,0,-kdx+ koord.x+i*koef.kx+1,max_y);
                if (draw_numbers_x)
                {
                        btmp->Canvas->TextOutA(-kdx+ koord.x+i*koef.kx-3,koord.y-18,FloatToStrF((i-1)*log_x+log_koord.x +1-ldx,ffFixed,8,0));
                }
        }

        for (int j = 1; j<iy+1; j++)
        {
                if (draw_setka)
                {
                        btmp->Canvas->Rectangle(0,koord.y-j*koef.ky,max_x,koord.y-j*koef.ky+1);
                        btmp->Canvas->Rectangle(0,koord.y+j*koef.ky,max_x,koord.y+j*koef.ky+1);                        
                }
                if (draw_numbers_y)
                {
                        btmp->Canvas->TextOutA(koord.x+3,koord.y-j*koef.ky-3,FloatToStrF(j*log_y+log_koord.y,ffFixed,8,0));
                        btmp->Canvas->TextOutA(koord.x+3,koord.y+j*koef.ky+3,"-"+FloatToStrF(j*log_y+log_koord.y,ffFixed,8,0));
                }
        }

        if (draw_kslines)
        {
                btmp->Canvas->Pen->Style = psSolid;
                btmp->Canvas->Pen->Color = clGray;
                btmp->Canvas->Rectangle(koord.x,koord.y,koord.x+max_x,koord.y+2);
                btmp->Canvas->Rectangle(koord.x-1,0,koord.x+1,max_y);
        }
        btmp->Canvas->MoveTo(koord.x,koord.y);
};


//------------------------------------------------------------------------------
// класс-"диаграмма"
//------------------------------------------------------------------------------
class TDiagram
{
public:
        TKoordSystem *ks;

        TLogPointList *lp_list;
        TVariantList <TImage> *img_list;

        TColor col;

        short line_thickness;
        short style;

        TDiagram(TKoordSystem *ksys,TChannelList *ChannelList);
        ~TDiagram();

        void DrawValue(TArchiveRecord *rec);
        void DrawPoint(TLogPoint *lp);
        void Draw7Point(T7Record *_7rec,TColor txtcol);
        void DrawLine(TLogPoint *p1, TLogPoint *val);
        void DrawNodeValue(TImage *p_img,TLogPoint *val);

        void DrawValue(TLogPoint *lp);

        void RedrawWithNodes();
        void RedrawWithOutNodes();
        void RedrawWithOutNodes(short freq_id);        
        void SplineByFormula(int n,tsysKoef koef,int mode_id,int speed_id);

        // сортировка узлов по x (0 - по возр., 1 - по убыванию)
        void SortNodes(int sort_id);

        void Redraw();
};
//------------------------------------------------------------------------------

TDiagram::TDiagram(TKoordSystem *ksys,TChannelList *ChannelList)
{
        lp_list = new TVariantList <TLogPoint>;
        img_list = new TVariantList <TImage>;

        ks = ksys;

        line_thickness = 1;
        style = psSolid;
};

TDiagram::~TDiagram()
{
        lp_list->DestroyList();
        delete lp_list;
        img_list->DestroyList();
        delete img_list;
};

void TDiagram::Redraw()
{
        ks->Redraw();
}

void TDiagram::DrawValue(TArchiveRecord *rec)
{
        TLogPoint lval;
//        lval.x = rec->date_time;
//        lval.y = (*rec->ChannelDataList)[data_id]->analog;

//        ks->DrawValue(lval,col);
};

void TDiagram::DrawPoint(TLogPoint *lp)
{
        ks->DrawPoint(lp,col);
};

void TDiagram::Draw7Point(T7Record *_7rec,TColor txtcol)
{
        ks->Draw7Point(_7rec,txtcol);
}

void TDiagram::DrawLine(TLogPoint *p1, TLogPoint *val)
{
        ks->DrawLine(p1,val,col,line_thickness,style);
};

void TDiagram::DrawValue(TLogPoint *lp)
{
        if (lp_list->count >= 2)
        {
                DrawLine((*lp_list)[lp_list->count-2],lp);
        }
};

void TDiagram::DrawNodeValue(TImage *new_img,TLogPoint *val)
{
        new_img->Width = 9;
        new_img->Height = 9;
        new_img->Canvas->Brush->Color = col; //?
        new_img->Canvas->Rectangle(new_img->ClientRect);
        ks->DrawNodeValue(new_img,val,col);
}

void TDiagram::RedrawWithNodes()
{
        for (int i=0; i<img_list->count; i++)
        {
                (*img_list)[i]->Visible = false;
        }

        for (int i=0; i<lp_list->count; i++)
        {
//              if ((*lp_list)[i]->x >= ks->log_koord.x) DrawNodeValue((*img_list)[i],(*lp_list)[i]);
                DrawNodeValue((*img_list)[i],(*lp_list)[i]);
//                else (*img_list)[i]->Visible = false;
        }
        for (int i=0; i<lp_list->count-1; i++)
        {
                DrawLine((*lp_list)[i],(*lp_list)[i+1]);
        }
}

void TDiagram::RedrawWithOutNodes()
{
    if (lp_list->count != 0)
    {
        for (int i=0; i<lp_list->count-1; i++)
        {
                int x1,y1;
                x1 = ks->koord.x+((*lp_list)[i]->x-ks->log_koord.x)/ks->log_x*ks->koef.kx;
                y1 = ks->koord.y-((*lp_list)[i]->y-ks->log_koord.y)/ks->log_y*ks->koef.ky;

                int x2,y2;
                x2 = ks->koord.x+((*lp_list)[i+1]->x-ks->log_koord.x)/ks->log_x*ks->koef.kx;
                y2 = ks->koord.y-((*lp_list)[i+1]->y-ks->log_koord.y)/ks->log_y*ks->koef.ky;

                if ( (x1 >= 0 && x1 <= ks->par_img->ClientWidth && y1 >= 0 && y1 <= ks->par_img->ClientHeight) ||
                     (x2 >= 0 && x2 <= ks->par_img->ClientWidth && y2 >= 0 && y2 <= ks->par_img->ClientHeight) )
                                        DrawLine((*lp_list)[i],(*lp_list)[i+1]);
        }
    }
}

void TDiagram::RedrawWithOutNodes(short fr_id)
{
    short freq_id;
    if (fr_id == 1) freq_id = 1;
    else freq_id = fr_id-1;

    if (lp_list->count != 0)
    {
        for (int i=0; i<lp_list->count-freq_id; i+=fr_id)
        {
                int x1,y1;
                x1 = ks->koord.x+((*lp_list)[i]->x-ks->log_koord.x)/ks->log_x*ks->koef.kx;
                y1 = ks->koord.y-((*lp_list)[i]->y-ks->log_koord.y)/ks->log_y*ks->koef.ky;

                int x2,y2;
                x2 = ks->koord.x+((*lp_list)[i+fr_id]->x-ks->log_koord.x)/ks->log_x*ks->koef.kx;
                y2 = ks->koord.y-((*lp_list)[i+fr_id]->y-ks->log_koord.y)/ks->log_y*ks->koef.ky;

                if ( (x1 >= 0 && x1 <= ks->par_img->ClientWidth && y1 >= 0 && y1 <= ks->par_img->ClientHeight) ||
                     (x2 >= 0 && x2 <= ks->par_img->ClientWidth && y2 >= 0 && y2 <= ks->par_img->ClientHeight) )
                                        DrawLine((*lp_list)[i],(*lp_list)[i+fr_id]);
        }
    }
}

void TDiagram::SplineByFormula(int n,tsysKoef koef,int mode_id,int speed_id)
{
        // разгон
        if (speed_id == 0)
        {
                float dx = 1.0/n;

                float x;

                // участок отхода
                for (x=0; x<=koef.mode_koefs[mode_id].L_oth; x += dx)
                {
                        TLogPoint *lp = new TLogPoint;

                        lp->x = koef.L_MAX-x;
                        lp->y = sqrt(2*koef.mode_koefs[mode_id].a_oth*x);
                        lp_list->Add(lp);
                }

                // участок разгона
                float ddd = koef.mode_koefs[mode_id].dL_razg;
                for (x = koef.mode_koefs[mode_id].L_oth-ddd; x < koef.mode_koefs[mode_id].L_oth+koef.mode_koefs[mode_id].L_razg-ddd; x += dx)
                {
                        TLogPoint *lp = new TLogPoint;

                        lp->x = koef.L_MAX-x-ddd;
                        lp->y = sqrt(2*koef.mode_koefs[mode_id].a_razg*x)+koef.mode_koefs[mode_id].dV_razg;
                        lp_list->Add(lp);
                }

                TLogPoint *lp = new TLogPoint;
                lp->x = koef.L_MAX-koef.mode_koefs[mode_id].L_razg-koef.mode_koefs[mode_id].L_oth;
                lp->y = koef.mode_koefs[mode_id].Vmax;
                lp_list->Add(lp);
        }

        // торможение
        if (speed_id == 1)
        {
                float dx = 1.0/n;

                float x;

                // участок замедления
                float ddd = 2.712;
                ddd = koef.mode_koefs[mode_id].dL_zam;
                for (x = koef.mode_koefs[mode_id].L_dot-ddd; x < koef.mode_koefs[mode_id].L_zam; x += dx)
                {
                        TLogPoint *lp = new TLogPoint;

                        lp->x = x+ddd;
                        lp->y = sqrt(2*koef.mode_koefs[mode_id].a_zam*x)+
                                +koef.mode_koefs[mode_id].dV_zam;
//                        lp->y = sqrt(2*koef.mode_koefs[mode_id].a_zam*(x+koef.mode_koefs[mode_id].dL_zam))+
  //                              +koef.mode_koefs[mode_id].dV_zam;
                        lp_list->Add(lp);
                }

                TLogPoint *lp = new TLogPoint;
                lp->x = koef.mode_koefs[mode_id].L_zam+ddd;
                lp->y = koef.mode_koefs[mode_id].Vmax;
                lp_list->Add(lp);
        }
}

void TDiagram::SortNodes(int sort_id)
{
        // по возрастанию
        if (sort_id == 0)
        {
                bool flag;
                TLogPoint tmp;
                for (int i = this->lp_list->count-2; i >= 0; i--)
                {
                        flag = false;
                        for (int j = 0; j <= i; j++)
                        {
                                if ((*this->lp_list)[j]->x > (*this->lp_list)[j+1]->x)
                                {
                                        tmp.x = (*this->lp_list)[j]->x;
                                        tmp.y = (*this->lp_list)[j]->y;

                                        (*this->lp_list)[j]->x = (*this->lp_list)[j+1]->x;
                                        (*this->lp_list)[j]->y = (*this->lp_list)[j+1]->y;

                                        (*this->lp_list)[j+1]->x = tmp.x;
                                        (*this->lp_list)[j+1]->y = tmp.y;

                                        flag = true;
                                }
                        }
                        if (!flag) break;
                }
        }

        // по убыванию
        if (sort_id == 1)
        {
                bool flag;
                TLogPoint tmp;
                for (int i = this->lp_list->count-2; i >= 0; i--)
                {
                        flag = false;
                        for (int j = 0; j <= i; j++)
                        {
                                if ((*this->lp_list)[j]->x < (*this->lp_list)[j+1]->x)
                                {
                                        tmp.x = (*this->lp_list)[j]->x;
                                        tmp.y = (*this->lp_list)[j]->y;

                                        (*this->lp_list)[j]->x = (*this->lp_list)[j+1]->x;
                                        (*this->lp_list)[j]->y = (*this->lp_list)[j+1]->y;

                                        (*this->lp_list)[j+1]->x = tmp.x;
                                        (*this->lp_list)[j+1]->y = tmp.y;

                                        flag = true;
                                }
                        }
                        if (!flag) break;
                }
        }
}

// Список должен быть отсортирован по-убыванию
float GetVFromList(float x,TLogPointList *lp_list)
{
        for (int i=0; i<lp_list->count-1; i++)
        {
                if ( x <= (*lp_list)[i]->x && x >= (*lp_list)[i+1]->x )
                {
                        float x1,x2,y1,y2;

                        // уравнение прямой по двум точкам
                        x1 = (*lp_list)[i]->x;
                        y1 = (*lp_list)[i]->y;
                        x2 = (*lp_list)[i+1]->x;
                        y2 = (*lp_list)[i+1]->y;

                        return (y2-y1)*(x-x1)/(x2-x1) + y1;
                }
        }

        return 0;
}

//----------------------------------------------------------------------
// "цикл подъема"
struct TCiklPod
{
        Word rhour;
        Word rmin;         // длительность цикла
        Word rsec;
//        int total_msec;

        TTime fbeg;

        Word phour;
        Word pmin;         // пауза
        Word psec;

        short vector;
        short mode;       // режим
        float P;          // эл.энергия за цикл
        bool vagon;
        float L;

        int begr;         // начальная запись
        int endr;         // конечная запись

        //-------------------- для РТП
        Word tphour;
        Word tpmin;
        Word tpsec;

        short reason;      // причина срабатывания РТП

        float atp;
        float Ltp;
        float Vtp;

        short n;           // номер цикла, к которому принадлежит РТП
};
//----------------------------------------------------------------------

// учетная запись
struct TLoginRecord
{
        char name[20];        // имя
        char group[20];       // категория пользования
        char tab_order[10];   // табельный номер
};

//----------------------------------------------------------------------
// информация о файле архива
struct TArcInfo
{
        char fname[60];     // директория+имя файла
        TDateTime date_time;// дата и время создания файла
        TArcFileState flag; // признак
};

// класс-каталог(список) архивов
class TArcCatalog
{
public:
        AnsiString fname;  // имя файла каталога

        TArcInfoList *list;

        TArcCatalog(AnsiString name,TSysParams *sp);
        ~TArcCatalog();

        short GetFirstFile(TArcFileState flag);
        short GetFileByName(AnsiString name);

        short DelFileFromDisk(AnsiString name);

        short Load();
        short Save();

        AnsiString ArcProgDir;
        short PackArchive(AnsiString f_name);
};

// упаковка архива стандартным архиватором (в д.с. RAR for Windows)
short TArcCatalog::PackArchive(AnsiString f_name)
{
        STARTUPINFO startin;
        PROCESS_INFORMATION pinfo;

        startin.cb = sizeof(STARTUPINFO);
        startin.lpReserved = NULL;
        startin.lpDesktop = NULL;
        startin.lpTitle = NULL;
        startin.dwFlags = STARTF_USESHOWWINDOW;
        startin.cbReserved2 = 0;
        startin.lpReserved2 = NULL;
        startin.wShowWindow = SW_SHOWMINIMIZED;

        AnsiString cmdLine = ArcProgDir;
        cmdLine += "\\WinRAR.exe a -df -ep1 ";
        cmdLine += f_name+".rar ";
        cmdLine += f_name+".arc ";
        cmdLine += f_name+".war";        

        CreateProcess(NULL,cmdLine.c_str(),
                      NULL,NULL,FALSE,0,
                      NULL,NULL,&startin,
                      &pinfo);

        return 0;
}

short TArcCatalog::Load()
{
        return list->ReadFromFile(fname);
}

short TArcCatalog::Save()
{
        return list->WriteToFile(fname);
}

short TArcCatalog::DelFileFromDisk(AnsiString name)
{
        short id = GetFileByName(name);

        AnsiString tname = name;

        if (id != -1)
        {
                if ((*list)[id]->flag == tafsCURRENT) tname += ".arc";
                else tname += ".rar";
                DeleteFile(tname);
                DeleteFile(name+".sta");
                DeleteFile(name+".war");                
                list->Del(id);
                return 0;
        }
        else return -1;
}

short TArcCatalog::GetFirstFile(TArcFileState flag)
{
        for (int i=0; i<list->count; i++)
        {
                if ( (*list)[i]->flag == flag )
                {
                        return i;
                }
        }

        return -1;
}

// name - имя файла (без расширения!!!)
short TArcCatalog::GetFileByName(AnsiString name)
{
        for (int i=0; i<list->count; i++)
        {
                if ( strcmp((*list)[i]->fname,name.c_str()) == 0 )
                {
                        return i;
                }
        }

        return -1;
}

TArcCatalog::TArcCatalog(AnsiString name,TSysParams *sp)
{
        fname = name;
        ArcProgDir = sp->RARArcDir;
        list = new TArcInfoList();
}

TArcCatalog::~TArcCatalog()
{
        list->DestroyList();
        delete list;
}

//----------------------------------------------------------------------
// класс-расписание звонков(событий)
struct TShedRecord
{
        TTime time;           // время звонка
        char StvolName[30];   // имя ствола
        char Phone[10];       // телефон
        TShedAction action;   // действие
        bool state;           // состояние записи (true-заблокировано false-активно)
};

class TSheduler
{
public:
        AnsiString fname;

        TShedRecordList *list;

        TSheduler(AnsiString name);
        ~TSheduler();

        short Load();
        short Save();
};

short TSheduler::Load()
{
        return list->ReadFromFile(fname);
}

short TSheduler::Save()
{
        return list->WriteToFile(fname);
}

TSheduler::TSheduler(AnsiString name)
{
        fname = name;
        list = new TShedRecordList();
}

TSheduler::~TSheduler()
{
        list->DestroyList();
        delete list;
}

//----------------------------------------------------------------------
struct TTimeStat
{
        TArcStat *stat;

        // измерение "Дата-Ствол-Рудник"
        short Smena;
        short Day;
        short Month;
        short Quarter;
        short HalfYear;
        short Year;
        short Stvol;
        short Rudnik;
};

void Stat2TimeStat(TArcStat *st,TTimeStat *tst)
{
        Word Year,Month,Day;
        DecodeDate(st->date_time,Year,Month,Day);

        tst->stat = st;

        tst->Day = Day;
        tst->Month = Month;
        tst->Year = Year;
        tst->Quarter = (Month-1)/3+1;
        tst->HalfYear = (Month-1)/6+1;

        tst->Smena = st->smena_id;
        tst->Stvol = st->StvolNameIndex;
        tst->Rudnik = st->RudNameIndex;
}

#endif
