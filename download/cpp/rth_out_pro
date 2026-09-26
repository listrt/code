/* rth_out_pro */
#ifndef rth_out_pro
#define rth_out_pro

#define rth_out_pro_runtime_normal_out
#define rth_out_pro_constant_out
#define rth_out_pro_runtime_fast_out

#include<rth_io>

#if defined(__LDBL_MAX__)
    #define LDBL_MAX_RT ((long double)__LDBL_MAX__)
#elif defined(_MSC_VER)
    #define LDBL_MAX_RT 1.79769313486231570815e+308L
#elif defined(__SIZEOF_LONG_DOUBLE__) && (__SIZEOF_LONG_DOUBLE__ == 4)
    #define LDBL_MAX_RT 3.40282346638528859812e+38L
#else
    #define LDBL_MAX_RT 1.79769313486231570815e+308L
#endif

namespace rttype{
    static constexpr unsigned ptr_w_rt=sizeof(void*)<<1;
}
#ifdef rth_out_pro_runtime_normal_out
namespace rttype{
    constexpr char hexlist[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    struct out_t{};
    static constexpr rttype::out_t out={};
}
namespace out_rth{
    namespace typetrait{
        template<typename T, typename U>
        struct is_same {
        static constexpr int v=0;
        };
        template<typename T>
        struct is_same<T, T> {
        static constexpr int v=1;
        };
        
        template<typename T>
        struct is_integer {
            static const int v=0;
        };
        template<typename T>
        struct is_integer<const T> : is_integer<T> {};
        template<typename T>
        struct is_integer<volatile T> : is_integer<T> {};
        template<typename T>
        struct is_integer<const volatile T> : is_integer<T> {};
        #define DEFINE_INTEGER_TYPE(T) \
        template<> struct is_integer<T> { static const int v=1;};
        DEFINE_INTEGER_TYPE(short)
        DEFINE_INTEGER_TYPE(unsigned short)
        DEFINE_INTEGER_TYPE(int)
        DEFINE_INTEGER_TYPE(unsigned int)
        DEFINE_INTEGER_TYPE(long)
        DEFINE_INTEGER_TYPE(unsigned long)
        DEFINE_INTEGER_TYPE(long long)
        DEFINE_INTEGER_TYPE(unsigned long long)
        #undef DEFINE_INTEGER_TYPE
        //UN
        template<typename T>
        struct is_unsigned_integer {
            static const int v=0;
        };
        
        template<typename T>
        struct is_unsigned_integer<const T> : is_unsigned_integer<T> {};
        template<typename T>
        struct is_unsigned_integer<volatile T> : is_unsigned_integer<T> {};
        template<typename T>
        struct is_unsigned_integer<const volatile T> : is_unsigned_integer<T> {};
        
        #define DEFINE_UNSIGNED_INTEGER_TYPE(T) \
        template<> struct is_unsigned_integer<T> { static const int v=1;};
        
        DEFINE_UNSIGNED_INTEGER_TYPE(unsigned short)
        DEFINE_UNSIGNED_INTEGER_TYPE(unsigned int)
        DEFINE_UNSIGNED_INTEGER_TYPE(unsigned long)
        DEFINE_UNSIGNED_INTEGER_TYPE(unsigned long long)
        
        #undef DEFINE_UNSIGNED_INTEGER_TYPE
        template<typename T>
        struct is_charptr {
            static const int v=0;
        };
        
        template<typename T>
        struct is_charptr<T*> {
            static const int v=is_charptr<T>::v;
        };
        template<>
        struct is_charptr<char> {
            static const int v=1;
        };
        template<>
        struct is_charptr<const char> {
            static const int v=1;
        };
        template<>
        struct is_charptr<volatile char> {
            static const int v=1;
        };
        template<>
        struct is_charptr<const volatile char> {
            static const int v=1;
        };
        //ptr
        template<typename T>
        struct is_ptr{static constexpr int v=0;};
        template<typename T>
        struct is_ptr<T*>{static constexpr int v=1;};
    }
}

namespace out_rth{
    namespace runtime{
        static inline char* lltoa(long long val, char* buf){
            char* p=buf+20;
            *p=0;
            unsigned long long u;
            if(val<0){
                u = (unsigned long long)(-val);
                do{
                    unsigned long long rem = u % 10;
                    *--p='0' | (char)rem;
                    u /= 10;
                }while(u);
                *--p='-';
            }
            else{
                u=(unsigned long long)val;
                do{
                    unsigned long long rem = u%10;
                    *--p='0' | (char)rem;
                    u/=10;
                }while (u);
            }
            return p;
        }
        static inline char* ulltoa(unsigned long long val, char* buf){
            char* p=buf+20;
            *p=0;
            do{
                unsigned long long rem = val % 10;
                *--p='0' | (char)rem;
                val/=10;
            }while(val);
            return p;
        }
        
        namespace out_fn{
            static inline int si(long long a){
                char c[21];
                char* p=lltoa(a,c);
                unsigned len=(c+20)-p;
                writer(p, len);
                return 0;
            }
            static inline int ui(unsigned long long a){
                char c[21];
                char* p=ulltoa(a,c);
                unsigned len=(c+20)-p;
                writer(p, len);
                return 0;
            }
            static inline int ch(char c){
                writer(&c,1);
                return 0;
            }
            static inline int cp(const char* c){
                unsigned l=0;
                while(*(c+l++));
                l--;
                writer(c,l);
                return 0;
            }
            template<typename T>
            static inline int vp(T* a){
                char c[rttype::ptr_w_rt+2]={};
                c[0]='0';
                c[1]='x';
                unsigned long long ax=(unsigned long long)a;
                for(int i=0;i<rttype::ptr_w_rt;i++){
                    int shift=(rttype::ptr_w_rt-1-i) <<2;
                    c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
                }
                writer(c,rttype::ptr_w_rt+2);
                return 0;
            }
            static inline int fp(long double a) {
                if (a==0) {
                    writer("0", 1);
                    return 0;
                }
                if (a!=a) {
                    writer("NaN", 3);
                    return 0;
                }
                char c[64];
                int idx = 0;
                bool neg = (a < 0);
                if (neg) a = -a;
                if (a > LDBL_MAX_RT) {
                    if (neg) writer("-INF", 4);
                    else     writer("INF", 3);
                    return 0;
                }
                constexpr long double ULL_MAX_P1 = 18446744073709551616.0L; //2^64
                if (a>=ULL_MAX_P1){
                    if (neg) writer("-INF", 4);
                    else     writer("INF", 3);
                    return 0;
                }
                unsigned long long ip = (unsigned long long)a;
                long double frac = a - (long double)ip;

                char buf[32];
                int bi = 0;
                do {
                    buf[bi++] = '0' ^ (int)(ip % 10);
                    ip /= 10;
                } while (ip);
                while (bi--) c[idx++] = buf[bi];

                c[idx++] = '.';

                for (int i = 0; i < 6; i++) {
                    frac *= 10;
                    int digit = (int)frac;
                    c[idx++] = '0' ^ digit;
                    frac -= digit;
                }

                while (idx > 0 && c[idx-1] == '0') idx--;
                if (idx > 0 && c[idx-1] == '.') idx--;

                writer(c, idx);
                return 0;
            }
        }
        #define defofn_fp(T) \
        static inline rttype::out_t outf(T a) {\
            out_fn::fp((long double)a);\
            return {};\
        }
        #define defofn_si(T) \
        static inline rttype::out_t outf(T a) {\
            out_fn::si((long long)a);\
            return {};\
        }
        #define defofn_ui(T) \
        static inline rttype::out_t outf(T a) {\
            out_fn::ui((unsigned long long)a);\
            return {};\
        }
        #define defofn_ch(T) \
        static inline rttype::out_t outf(T a) {\
            const char c=static_cast<char>(a);\
            writer(&c,1);\
            return {};\
        }
        defofn_fp(float);
        defofn_fp(double);
        defofn_fp(long double);

        defofn_si(short);
        defofn_si(int);
        defofn_si(long);
        defofn_si(long long);

        defofn_ui(unsigned short);
        defofn_ui(unsigned int);
        defofn_ui(unsigned long);
        defofn_ui(unsigned long long);

        defofn_ch(char);
        defofn_ch(signed char);
        defofn_ch(unsigned char);
        
        #undef defofn_fp
        #undef defofn_si
        #undef defofn_ui
        #undef defofn_ch
        static inline rttype::out_t outf(char* a){
            out_fn::cp(a);
            return {};
        }
        static inline rttype::out_t outf(const char* a){
            out_fn::cp(a);
            return {};
        }
        static inline rttype::out_t outf(bool a) {
            if(a){writer("1",1);}
            else{writer("0",1);}
            return {};
        }
        template<typename T>
        static inline rttype::out_t outf(T* a){
            out_fn::vp(a);
            return {};
        }
    }
}
#define def_op_rtout_si(T) \
static inline rttype::out_t operator<<(rttype::out_t a, T b){\
    out_rth::runtime::out_fn::si(b);\
    return a;\
}
#define def_op_rtout_ui(T) \
static inline rttype::out_t operator<<(rttype::out_t a, T b){\
    out_rth::runtime::out_fn::ui(b);\
    return a;\
}
#define def_op_rtout_fp(T) \
static inline rttype::out_t operator<<(rttype::out_t a, T b){\
    out_rth::runtime::out_fn::fp(b);\
    return a;\
}
#define def_op_rtout_ch(T) \
static inline rttype::out_t operator<<(rttype::out_t a, T b){\
    const char c=static_cast<char>(b);\
    writer(&c,1);\
    return a;\
}
def_op_rtout_si(short);
def_op_rtout_si(int);
def_op_rtout_si(long);
def_op_rtout_si(long long);

def_op_rtout_ui(unsigned short);
def_op_rtout_ui(unsigned int);
def_op_rtout_ui(unsigned long);
def_op_rtout_ui(unsigned long long);

def_op_rtout_fp(float);
def_op_rtout_fp(double);
def_op_rtout_fp(long double);

def_op_rtout_ch(char);
def_op_rtout_ch(signed char);
def_op_rtout_ch(unsigned char);

#undef def_op_rtout_fp
#undef def_op_rtout_si
#undef def_op_rtout_ui
#undef def_op_rtout_ch
template<typename T>
static inline rttype::out_t operator<<(rttype::out_t a, T b) {
    out_rth::runtime::outf(b);
    return a;
}
template<typename T>
static inline rttype::out_t operator<<(rttype::out_t a, T* b) {
    out_rth::runtime::out_fn::vp(b);
    return a;
}
static inline rttype::out_t operator<<(rttype::out_t a, char* b) {
    out_rth::runtime::out_fn::cp(b);
    return a;
}
static inline rttype::out_t operator<<(rttype::out_t a, const char* b) {
    unsigned l=0;
    while (b[l]) l++;
    writer(b, l);
    return a;
}
static inline rttype::out_t operator<<(rttype::out_t a, rttype::out_t (*manip)(rttype::out_t)) {
    return manip(a);
}

namespace rttype{
    static inline rttype::out_t endl(rttype::out_t a) {
        const char n = '\n';
        writer(&n, 1);
        return a;
    }

    static inline rttype::out_t flush(rttype::out_t a) {
        return a;
    }
}
#endif//rth_out_pro_runtime_normal_out

#ifdef rth_out_pro_constant_out
namespace out_rth{
    namespace constant{
        using len_t=unsigned;
        template<len_t N=256>
        struct constantout_t{
            char c[N]={};
            len_t l=0;//No include '\0'
            constexpr const char* c_str() const{return c;}
            constexpr len_t       size()  const{return l;}
            template<len_t M>
            constexpr constantout_t& operator=(const constantout_t<M>& a){
                len_t cmP=M>N?N:M;
                l=a.l;
                len_t i=0;
                for(;i<cmP;i++){
                    c[i]=a.c[i];
                }
                for(;i<N;i++){
                    c[i]=0;
                }
                l=(a.l<N)? a.l:N;
                return (*this);
            }
        };
        //+
        template<len_t N,len_t M>
        static inline constexpr constantout_t<N+M> operator+(constantout_t<N> a,constantout_t<M> b){
            constantout_t<N+M> r=a;
            len_t i=a.l;
            for(;i<a.l+b.l;i++)r.c[i]=b.c[i-a.l];
            r.l=i;
            return r;
        }
        template<len_t N>
        static inline constexpr constantout_t<N+1> operator+(constantout_t<N> a,char b){
            constantout_t<N+1> r=a;
            r.c[r.l]=b;
            r.l++;
            return r;
        }
        template<len_t N>
        static inline constexpr constantout_t<N+1> operator+(char b,constantout_t<N> a){
            constantout_t<N+1> r{};
            for(len_t i=1;i<=N;i++)r.c[i]=a.c[i-1];
            r.c[0]=b;
            r.l=a.l+1;
            return r;
        }
        //<<
        template<len_t N,len_t M>
        static inline constexpr constantout_t<N+M> operator<<(constantout_t<N> a,constantout_t<M> b){
            constantout_t<N+M> r=a;
            len_t i=a.l;
            for(;i<a.l+b.l;i++)r.c[i]=b.c[i-a.l];
            r.l=i;
            return r;
        }
        template<len_t N>
        static inline constexpr constantout_t<N+1> operator<<(constantout_t<N> a,char b){
            constantout_t<N+1> r=a;
            r.c[r.l]=b;
            r.l++;
            return r;
        }
        template<len_t N>
        static inline constexpr constantout_t<N+1> operator<<(char b,constantout_t<N> a){
            constantout_t<N+1> r{};
            for(len_t i=1;i<=N;i++)r.c[i]=a.c[i-1];
            r.c[0]=b;
            r.l=a.l+1;
            return r;
        }
        //*
        template<len_t N>
        constexpr constantout_t<N> operator*(const constantout_t<N>& a, len_t b) {
            constantout_t<N> r{};
            len_t i = 0;
            for (len_t t = 0; t < b; ++t)
                for (len_t j = 0; j < a.l && i < N - 1; ++j)
                    r.c[i++] = a.c[j];
            r.l=i;
            return r;
        }
        template<len_t N>
        constexpr constantout_t<N> operator*(len_t b,const constantout_t<N>& a) {
            constantout_t<N> r{};
            len_t i = 0;
            for (len_t t = 0; t < b; ++t)
                for (len_t j = 0; j < a.l && i < N - 1; ++j)
                    r.c[i++] = a.c[j];
            r.l=i;
            return r;
        }
        static inline constexpr char* lltoa(long long val, char* buf){
	        char* p=buf+20;
	        *p=0;
	        unsigned long long u=0;
	        if(val<0){
	            u = (unsigned long long)(-val);
	            do{
	                unsigned long long rem = u % 10;
	                *--p=48 | (char)rem;
	                u /= 10;
	            }while(u);
	            *--p='-';
	        }
	        else{
	            u=(unsigned long long)val;
	            do{
	                unsigned long long rem = u%10;
	                *--p=48 | (char)rem;
	                u/=10;
	            }while (u);
	        }
	        return p;
	    }   
	    static inline constexpr char* ulltoa(unsigned long long val, char* buf){
	        char* p=buf+20;
	        *p=0;
	        do{
	            unsigned long long rem = val % 10;
	            *--p=48 | (char)rem;
	            val/=10;
	        }while(val);
	        return p;
	    }
        //out_fn
        namespace out_fn{
            static inline constexpr constantout_t<20> si(long long a) {
                constantout_t<20> b{};
                char tmp[21]={};
                char* p=lltoa(a, tmp);
                unsigned len=20-(p-tmp);
                for(unsigned i=0; i < len && i<21-1;i++) b.c[i]=p[i];
                b.l=len;
                return b;
            }
            static inline constexpr constantout_t<20> ui(unsigned long long a) {
                constantout_t<20> b{};
                char tmp[21]={};
                char* p=ulltoa(a, tmp);
                unsigned len=20-(p-tmp);
                for(unsigned i=0; i < len && i<21-1;i++) b.c[i]=p[i];
                b.l=len;
                return b;
            }
            static inline constexpr constantout_t<1>  ch(char a){
                constantout_t<1> r{};
                r.c[0]=a;
                r.l=1;
                return r;
            }
            static inline constexpr constantout_t<1>  ch(signed char a){
                constantout_t<1> r{};
                r.c[0]=static_cast<char>(a);
                r.l=1;
                return r;
            }
            static inline constexpr constantout_t<1>  ch(unsigned char a){
                constantout_t<1> r{};
                r.c[0]=static_cast<char>(a);
                r.l=1;
                return r;
            }
            static inline constexpr constantout_t<256>cp(const char* a){
                constantout_t<256> r{};
                len_t i=0;
                for(;i<256;i++){
                    if((a[i])){
                        r.c[i]=*(a+i);
                    }else{
                        break;
                    }
                }
                r.l=i;
                return r;
            }
            template<typename T>
            static inline constexpr constantout_t<rttype::ptr_w_rt+2> vp(T* a){
                constantout_t<rttype::ptr_w_rt+2> r{};
                r.c[0]='0';
                r.c[1]='x';
                unsigned long long ax=(unsigned long long)a;
                for(int i=0;i<rttype::ptr_w_rt;i++){
                    int shift=(rttype::ptr_w_rt-1-i) <<2;
                    r.c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
                }
                r.l=rttype::ptr_w_rt+2;
                return r;
            }
            static inline constexpr constantout_t<35> fp(long double a) {
                constantout_t<35> b{};
                if (a==0.0L) { b.c[0]='0'; b.l=1; return b; }
                if (a!=a) { b.c[0]='N';
                            b.c[1]='a';
                            b.c[2]='N';
                b.l=3;return b;}
                bool neg=false;
                if (a < 0.0L) { neg = true; a = -a; }
                if (a > LDBL_MAX_RT) {
                    unsigned i = 0;
                    if (neg) b.c[i++] = '-';
                    b.c[i++]='I'; b.c[i++]='N'; b.c[i++]='F';
                    b.l = i; return b;
                }
                constexpr long double ULL_MAX_P1 = 18446744073709551616.0L; // 2^64
                if (a >= ULL_MAX_P1) {
                    unsigned i=0;
                    if (neg) b.c[i++]='-';
                    b.c[i++]='I';b.c[i++]='N';b.c[i++]='F';
                    b.l=i; return b;
                }
                unsigned long long ip = (unsigned long long)a;
                long double frac = a - (long double)ip;
                unsigned long long frac6 = (unsigned long long)(frac * 1000000.0L + 0.5L);
                if (frac6 >= 1000000ULL) {
                    frac6 = 0;
                    if (ip == 0xFFFFFFFFFFFFFFFFULL) {
                        unsigned i = 0;
                        if (neg) b.c[i++] = '-';
                        b.c[i++]='I'; b.c[i++]='N'; b.c[i++]='F';
                        b.l = i; return b;
                    }
                    ip++;
                }
                char t[32] = {};
                unsigned n = 0;
                if (neg) t[n++] = '-';
                char tmp[24] = {};
                int tn = 0;
                do { tmp[tn++] = (char)('0' ^ (int)(ip % 10)); ip /= 10; } while (ip);
                while (tn--) t[n++] = tmp[tn];
                t[n++] = '.';
                char fbuf[6] = {};
                for (int i = 5; i >= 0; i--) { fbuf[i] = (char)('0' ^ (int)(frac6 % 10)); frac6 /= 10; }
                for (int i = 0; i < 6; i++) t[n++] = fbuf[i];
                unsigned dot = 0;
                for (unsigned i = 0; i < n; i++) if (t[i] == '.') { dot = i; break; }
                while (n > dot + 1 && t[n-1] == '0') n--;
                if (n == dot + 1) n = dot;
                if (n == 2 && t[0] == '-' && t[1] == '0') { t[0] = '0'; n = 1; }
                unsigned m = (n < 35) ? n : 35;
                for (unsigned i = 0; i < m; i++) b.c[i] = t[i];
                b.l = m;
                return b;
            }
            namespace morecp{
                static inline constexpr constantout_t<1024> bk(const char* a){
                    constantout_t<1024> r{};
                    len_t i=0;
                    for(;i<1024;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
                static inline constexpr constantout_t<2048> wk(const char* a){
                    constantout_t<2048> r{};
                    len_t i=0;
                    for(;i<2048;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
                static inline constexpr constantout_t<4096> dk(const char* a){
                    constantout_t<4096> r{};
                    len_t i=0;
                    for(;i<4096;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
            }
        }
        #define defsiop(T) \
        template<len_t N>\
        static inline constexpr constantout_t<N+20> operator<<(constantout_t<N> a,T b){\
            auto g=out_fn::si(b);\
            constantout_t<N+20> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=a.l+g.l;\
            return r;\
        }
        #define defuiop(T) \
        template<len_t N>\
        static inline constexpr constantout_t<N+20> operator<<(constantout_t<N> a,T b){\
            auto g=out_fn::ui(b);\
            constantout_t<N+20> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=a.l+g.l;\
            return r;\
        }
        #define defchop(T) \
        template<len_t N>\
        static inline constexpr constantout_t<N+1> operator<<(constantout_t<N> a,T b){\
            constantout_t<N+1> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            r.c[a.l]=static_cast<char>(b);\
            r.l=a.l+1;\
            return r;\
        }
        #define defcpop(T) \
        template<len_t N>\
        static inline constexpr constantout_t<N+256> operator<<(constantout_t<N> a,T b){\
            constantout_t<256> g=out_fn::cp(b);\
            constantout_t<N+256> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=g.l+a.l;\
            return r;\
        }
        #define deffpop(T) \
        template<len_t N>\
        static inline constexpr constantout_t<N+35> operator<<(constantout_t<N> a,T b){\
            auto g=out_fn::fp(b);\
            constantout_t<N+35> r={};\
            for(len_t i=0;i<a.l;i++){\
                r.c[i]=a.c[i];\
            }\
            for(len_t i=0;i<g.l;i++){\
                r.c[i+a.l]=g.c[i];\
            }\
            r.l=a.l+g.l;\
            return r;\
        }

        defsiop(short);
        defsiop(int);
        defsiop(long);
        defsiop(long long);

        defuiop(unsigned short);
        defuiop(unsigned);
        defuiop(unsigned long);
        defuiop(unsigned long long);

        //defchop(char);
        defchop(signed char);
        defchop(unsigned char);

        defcpop(char*);
        defcpop(const char*);

        deffpop(float);
        deffpop(double);
        deffpop(long double);

        #undef defsiop
        #undef defuiop
        #undef defchop
        #undef defcpop
        #undef deffpop
        template<typename T,len_t N>
        static inline constexpr constantout_t<N+rttype::ptr_w_rt+2> operator<<(constantout_t<N> a,T* b){
            auto g=out_fn::vp(b);
            constantout_t<N+rttype::ptr_w_rt+2> r={};
            for(len_t i=0;i<a.l;i++){
                r.c[i]=a.c[i];
            }
            for(len_t i=0;i<g.l;i++){
                r.c[i+a.l]=g.c[i];
            }
            r.l=a.l+g.l;
            return r;
        }
    }
}
#endif//rth_out_pro_constant_out

#ifdef rth_out_pro_runtime_fast_out
namespace out_rth{
    namespace fastrt{
        using len_t=unsigned;
        struct out{};
        struct outc{};
        template<len_t N=256>
        struct fastout_t{
            char c[N]={};
            len_t l=0;//No include '\0'
            const char* c_str() const{return c;}
            len_t       size()  const{return l;}
            template<len_t M>
            fastout_t& operator=(const fastout_t<M>& a){
                len_t cmP=M>N?N:M;
                l=a.l;
                len_t i=0;
                for(;i<cmP;i++){
                    c[i]=a.c[i];
                }
                for(;i<N;i++){
                    c[i]=0;
                }
                l=(a.l<N)? a.l:N;
                return (*this);
            }
        };
        //+
        template<len_t N,len_t M>
        static inline fastout_t<N+M> operator+(fastout_t<N> a,fastout_t<M> b){
            fastout_t<N+M> r=a;
            len_t i=a.l;
            for(;i<a.l+b.l;i++)r.c[i]=b.c[i-a.l];
            r.l=i;
            return r;
        }
        template<len_t N>
        static inline fastout_t<N+1> operator+(fastout_t<N> a,char b){
            fastout_t<N+1> r=a;
            r.c[r.l]=b;
            r.l++;
            return r;
        }
        template<len_t N>
        static inline fastout_t<N+1> operator+(char b,fastout_t<N> a){
            fastout_t<N+1> r{};
            for(len_t i=1;i<=N;i++)r.c[i]=a.c[i-1];
            r.c[0]=b;
            r.l=a.l+1;
            return r;
        }
        //<<
        template<len_t N,len_t M>
        static inline fastout_t<N+M> operator<<(fastout_t<N> a,fastout_t<M> b){
            fastout_t<N+M> r=a;
            len_t i=a.l;
            for(;i<a.l+b.l;i++)r.c[i]=b.c[i-a.l];
            r.l=i;
            return r;
        }
        template<len_t N>
        static inline fastout_t<N+1> operator<<(fastout_t<N> a,char b){
            fastout_t<N+1> r=a;
            r.c[r.l]=b;
            r.l++;
            return r;
        }
        template<len_t N>
        static inline fastout_t<N+1> operator<<(char b,fastout_t<N> a){
            fastout_t<N+1> r{};
            for(len_t i=1;i<=N;i++)r.c[i]=a.c[i-1];
            r.c[0]=b;
            r.l=a.l+1;
            return r;
        }
        //*
        template<len_t N>
        fastout_t<N> operator*(const fastout_t<N>& a, len_t b) {
            fastout_t<N> r{};
            len_t i = 0;
            for (len_t t = 0; t < b; ++t)
                for (len_t j = 0; j < a.l && i < N - 1; ++j)
                    r.c[i++] = a.c[j];
            r.l=i;
            return r;
        }
        template<len_t N>
        fastout_t<N> operator*(len_t b,const fastout_t<N>& a) {
            fastout_t<N> r{};
            len_t i = 0;
            for (len_t t = 0; t < b; ++t)
                for (len_t j = 0; j < a.l && i < N - 1; ++j)
                    r.c[i++] = a.c[j];
            r.l=i;
            return r;
        }
        static inline char* lltoa(long long val, char* buf){
	        char* p=buf+20;
	        *p=0;
	        unsigned long long u=0;
	        if(val<0){
	            u = (unsigned long long)(-val);
	            do{
	                unsigned long long rem = u % 10;
	                *--p=48 | (char)rem;
	                u /= 10;
	            }while(u);
	            *--p='-';
	        }
	        else{
	            u=(unsigned long long)val;
	            do{
	                unsigned long long rem = u%10;
	                *--p=48 | (char)rem;
	                u/=10;
	            }while (u);
	        }
	        return p;
	    }   
	    static inline char* ulltoa(unsigned long long val, char* buf){
	        char* p=buf+20;
	        *p=0;
	        do{
	            unsigned long long rem = val % 10;
	            *--p=48 | (char)rem;
	            val/=10;
	        }while(val);
	        return p;
	    }
        //out_fn
        namespace out_fn{
            static inline fastout_t<20> si(long long a) {
                fastout_t<20> b{};
                char tmp[21]={};
                char* p=lltoa(a, tmp);
                unsigned len=20-(p-tmp);
                for(unsigned i=0; i < len && i<21-1;i++) b.c[i]=p[i];
                b.l=len;
                return b;
            }
            static inline fastout_t<20> ui(unsigned long long a) {
                fastout_t<20> b{};
                char tmp[21]={};
                char* p=ulltoa(a, tmp);
                unsigned len=20-(p-tmp);
                for(unsigned i=0; i < len && i<21-1;i++) b.c[i]=p[i];
                b.l=len;
                return b;
            }
            static inline fastout_t<1>  ch(char a){
                fastout_t<1> r{};
                r.c[0]=a;
                r.l=1;
                return r;
            }
            static inline fastout_t<1>  ch(signed char a){
                fastout_t<1> r{};
                r.c[0]=static_cast<char>(a);
                r.l=1;
                return r;
            }
            static inline fastout_t<1>  ch(unsigned char a){
                fastout_t<1> r{};
                r.c[0]=static_cast<char>(a);
                r.l=1;
                return r;
            }
            static inline fastout_t<256>cp(const char* a){
                fastout_t<256> r{};
                len_t i=0;
                for(;i<256;i++){
                    if((a[i])){
                        r.c[i]=*(a+i);
                    }else{
                        break;
                    }
                }
                r.l=i;
                return r;
            }
            template<typename T>
            static inline fastout_t<rttype::ptr_w_rt+2> vp(T* a){
                fastout_t<rttype::ptr_w_rt+2> r{};
                r.c[0]='0';
                r.c[1]='x';
                unsigned long long ax=(unsigned long long)a;
                for(int i=0;i<rttype::ptr_w_rt;i++){
                    int shift=(rttype::ptr_w_rt-1-i) <<2;
                    r.c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
                }
                r.l=rttype::ptr_w_rt+2;
                return r;
            }
            static inline fastout_t<35> fp(long double a) {
                fastout_t<35> b{};
                if (a==0.0L) { b.c[0]='0'; b.l=1; return b; }
                if (a!=a) { b.c[0]='N';
                            b.c[1]='a';
                            b.c[2]='N';
                b.l=3;return b;}
                bool neg=false;
                if (a < 0.0L) { neg = true; a = -a; }
                if (a > LDBL_MAX_RT) {
                    unsigned i = 0;
                    if (neg) b.c[i++] = '-';
                    b.c[i++]='I'; b.c[i++]='N'; b.c[i++]='F';
                    b.l = i; return b;
                }
                constexpr long double ULL_MAX_P1 = 18446744073709551616.0L; // 2^64
                if (a >= ULL_MAX_P1) {
                    unsigned i=0;
                    if (neg) b.c[i++]='-';
                    b.c[i++]='I';b.c[i++]='N';b.c[i++]='F';
                    b.l=i; return b;
                }
                unsigned long long ip = (unsigned long long)a;
                long double frac = a - (long double)ip;
                unsigned long long frac6 = (unsigned long long)(frac * 1000000.0L + 0.5L);
                if (frac6 >= 1000000ULL) {
                    frac6 = 0;
                    if (ip == 0xFFFFFFFFFFFFFFFFULL) {
                        unsigned i = 0;
                        if (neg) b.c[i++] = '-';
                        b.c[i++]='I'; b.c[i++]='N'; b.c[i++]='F';
                        b.l = i; return b;
                    }
                    ip++;
                }
                char t[32] = {};
                unsigned n = 0;
                if (neg) t[n++] = '-';
                char tmp[24] = {};
                int tn = 0;
                do { tmp[tn++] = (char)('0' ^ (int)(ip % 10)); ip /= 10; } while (ip);
                while (tn--) t[n++] = tmp[tn];
                t[n++] = '.';
                char fbuf[6] = {};
                for (int i = 5; i >= 0; i--) { fbuf[i] = (char)('0' ^ (int)(frac6 % 10)); frac6 /= 10; }
                for (int i = 0; i < 6; i++) t[n++] = fbuf[i];
                unsigned dot = 0;
                for (unsigned i = 0; i < n; i++) if (t[i] == '.') { dot = i; break; }
                while (n > dot + 1 && t[n-1] == '0') n--;
                if (n == dot + 1) n = dot;
                if (n == 2 && t[0] == '-' && t[1] == '0') { t[0] = '0'; n = 1; }
                unsigned m = (n < 35) ? n : 35;
                for (unsigned i = 0; i < m; i++) b.c[i] = t[i];
                b.l = m;
                return b;
            }
            namespace morecp{
                static inline fastout_t<1024> bk(const char* a){
                    fastout_t<1024> r{};
                    len_t i=0;
                    for(;i<1024;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
                static inline fastout_t<2048> wk(const char* a){
                    fastout_t<2048> r{};
                    len_t i=0;
                    for(;i<2048;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
                static inline fastout_t<4096> dk(const char* a){
                    fastout_t<4096> r{};
                    len_t i=0;
                    for(;i<4096;i++){
                        if((a[i])){
                            r.c[i]=*(a+i);
                        }else{
                            break;
                        }
                    }
                    r.l=i;
                    return r;
                }
            }
        }
        #define defsiop(T) \
        template<len_t N>\
        static inline fastout_t<N+20> operator<<(fastout_t<N> a,T b){\
            auto g=out_fn::si(b);\
            fastout_t<N+20> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=a.l+g.l;\
            return r;\
        }
        #define defuiop(T) \
        template<len_t N>\
        static inline fastout_t<N+20> operator<<(fastout_t<N> a,T b){\
            auto g=out_fn::ui(b);\
            fastout_t<N+20> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=a.l+g.l;\
            return r;\
        }
        #define defchop(T) \
        template<len_t N>\
        static inline fastout_t<N+1> operator<<(fastout_t<N> a,T b){\
            fastout_t<N+1> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            r.c[a.l]=static_cast<char>(b);\
            r.l=a.l+1;\
            return r;\
        }
        #define defcpop(T) \
        template<len_t N>\
        static inline fastout_t<N+256> operator<<(fastout_t<N> a,T b){\
            fastout_t<256> g=out_fn::cp(b);\
            fastout_t<N+256> r={};\
            for(len_t i=0;i<a.l;i++){r.c[i]=a.c[i];}\
            for(len_t i=0;i<g.l;i++){r.c[i+a.l]=g.c[i];}\
            r.l=g.l+a.l;\
            return r;\
        }
        #define deffpop(T) \
        template<len_t N>\
        static inline fastout_t<N+35> operator<<(fastout_t<N> a,T b){\
            auto g=out_fn::fp(b);\
            fastout_t<N+35> r={};\
            for(len_t i=0;i<a.l;i++){\
                r.c[i]=a.c[i];\
            }\
            for(len_t i=0;i<g.l;i++){\
                r.c[i+a.l]=g.c[i];\
            }\
            r.l=a.l+g.l;\
            return r;\
        }

        defsiop(short);
        defsiop(int);
        defsiop(long);
        defsiop(long long);

        defuiop(unsigned short);
        defuiop(unsigned);
        defuiop(unsigned long);
        defuiop(unsigned long long);

        //defchop(char);
        defchop(signed char);
        defchop(unsigned char);

        defcpop(char*);
        defcpop(const char*);

        deffpop(float);
        deffpop(double);
        deffpop(long double);

        #undef defsiop
        #undef defuiop
        #undef defchop
        #undef defcpop
        #undef deffpop
        template<typename T,len_t N>
        static inline fastout_t<N+rttype::ptr_w_rt+2> operator<<(fastout_t<N> a,T* b){
            auto g=out_fn::vp(b);
            fastout_t<N+rttype::ptr_w_rt+2> r={};
            for(len_t i=0;i<a.l;i++){
                r.c[i]=a.c[i];
            }
            for(len_t i=0;i<g.l;i++){
                r.c[i+a.l]=g.c[i];
            }
            r.l=a.l+g.l;
            return r;
        }
        template<len_t N>
        static inline fastout_t<N> operator<<(fastout_t<N> a,out){
            writer(a.c,a.l);
            return a;
        }
        template<len_t N>
        static inline fastout_t<N> operator<<(fastout_t<N> a,outc){
            writer(a.c,a.l);
            return {};
        }
    }
}
#endif

#endif/**/
