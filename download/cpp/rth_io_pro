#ifndef rth_io_pro
#define rth_io_pro

#include<rth_io>
namespace rttype{
    static constexpr int ptr_w_rt=sizeof(void*)<<1;
}
#if __cplusplus >= 199711L
namespace rttype{
    constexpr char hexlist[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
    enum state_io{
        in_=0,out_=1,err_=2
    };
    struct oitype{
        state_io s=err_;
        int c=0;
    };
    static constexpr rttype::oitype out={out_,1};
    static constexpr rttype::oitype in={in_,1};
}
namespace rth_io{
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
    DEFINE_INTEGER_TYPE(bool)
    DEFINE_INTEGER_TYPE(char)
    DEFINE_INTEGER_TYPE(signed char)
    DEFINE_INTEGER_TYPE(unsigned char)
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

    static char* lltoa(long long val, char* buf){
	    char* p=buf+20;
	    *p^=(*p);
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
	static char* ulltoa(unsigned long long val, char* buf){
	    char* p=buf+20;
	    *p^=(*p);
	    do{
	        unsigned long long rem = val % 10;
	        *--p='0' | (char)rem;
	        val/=10;
	    }while(val);
	    return p;
	}
    namespace out_fn{
        static int si(long long a){
            char c[21];
            char* p=lltoa(a,c);
            unsigned len=(c+20)-p;
            writer(p, len);
            return 0;
        }
        static int ui(unsigned long long a){
            char c[21];
            char* p=ulltoa(a,c);
            unsigned len=(c+20)-p;
            writer(p, len);
            return 0;
        }
        static int ch(char c){
            writer(&c,1);
            return 0;
        }
        static int cp(const char* c){
            unsigned l=0;
            while(*(c+l++));
            writer(c,l);
            return 0;
        }
        template<typename T>//ptr
        static int vp(T* a){
	        #if __cplusplus>=201103L
            char c[rttype::ptr_w_rt+2]={[0]='0',[1]='x'};
            unsigned long long ax=(unsigned long long)a;
            for (int i=0; i < rttype::ptr_w_rt; i++) {
			        int shift=(rttype::ptr_w_rt-1-i) <<2;
			        c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
			    }
			writer(c,rttype::ptr_w_rt+2);
            return 0;
            #else
            char c[18];
            c[0]='0';
            c[1]='x';
            unsigned long long ax=(unsigned long long)a;
            for (int i=0;i<rttype::ptr_w_rt; i++) {
			        int shift=(rttype::ptr_w_rt-1-i)<<2;
			        c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
			}
            writer(c,18);
            return 0;
            #endif
        }
        static int fp(long double a) {
            if (a==0) {
                writer("0", 1);
                return 0;
            }
            char c[64];
            int idx=0;
            if (a < 0) {
                c[idx++]='-';
                a=-a;
            }
            
            unsigned long long ip = (unsigned long long)a;
            long double frac=a-(long double)ip;
            
            char buf[32];
            int bi = 0;
            do {
                buf[bi++] = '0' + (int)(ip % 10);
                ip /= 10;
            } while (ip);
            while (bi--) c[idx++] = buf[bi];
            
            c[idx++] = '.';
            
            for (int i=0;i<6;i++) {
                frac *= 10;
                int digit = (int)frac;
                c[idx++] = '0' + digit;
                frac -= digit;
            }
            
            while (idx > 0 && c[idx-1] == '0') idx--;
            if (idx > 0 && c[idx-1] == '.') idx--;
            
            writer(c, idx);
            return 0;
        }
    }

    static rttype::oitype outf(float a) {
        out_fn::fp((long double)a);
        return {rttype::out_, 1};
    }

    static rttype::oitype outf(double a) {
        out_fn::fp((long double)a);
        return {rttype::out_, 1};
    }

    static rttype::oitype outf(long double a) {
        out_fn::fp(a);
        return {rttype::out_, 1};
    }
    static rttype::oitype outf(bool a) {
        if(a){writer("1",2);}
        else{writer("0",2);}
        return {rttype::out_, 1};
    }
    template<typename T>
    static rttype::oitype outf(T* a){
        out_fn::vp(a);
        return {rttype::out_, 1};
    }
    template<typename T>
    static rttype::oitype outf(T a) {
        rttype::oitype result = {rttype::out_, 1};
        if(rth_io::is_integer<T>::v){
            if(is_unsigned_integer<T>::v){
                out_fn::ui((unsigned long long)a);
                return result;
            }else{
                out_fn::si((long long )a);
                return result;
            }
        }else if(rth_io::is_charptr<T>::v){
            out_fn::cp((const char*)a);
            return result;
        }else{
            out_fn::si(int(a));
            return result;
        }
    }
}


template<typename T>
static rttype::oitype operator<<(rttype::oitype a, T b) {
    if (a.c != 1) {
        rttype::oitype err = {rttype::err_, 0};
        return err;
    }
    
    if (a.s == rttype::out_) {
        rth_io::outf(b);
    } else if (a.s == rttype::in_) {
        rttype::oitype err = {rttype::err_, 0};
        return err;
    }
    
    return a;
}

static inline rttype::oitype operator<<(rttype::oitype a, char* b) {
    if (a.c != 1 || a.s != rttype::out_) {
        rttype::oitype err = {rttype::err_, 0};
        return err;
    }
    rth_io::out_fn::cp(b);
    return a;
}

static inline rttype::oitype operator<<(rttype::oitype a, const char* b) {
    if (a.c != 1 || a.s != rttype::out_) {
        rttype::oitype err = {rttype::err_, 0};
        return err;
    }
    unsigned l = 0;
    while (b[l]) l++;
    writer(b, l);
    return a;
}

static inline rttype::oitype operator<<(rttype::oitype a, rttype::oitype (*manip)(rttype::oitype)) {
    return manip(a);
}
namespace rttype{
    static inline rttype::oitype endl(rttype::oitype a) {
        if (a.s == rttype::out_) {
            const char n = '\n';
            writer(&n, 1);
        }
        return a;
    }

    static inline rttype::oitype flush(rttype::oitype a) {
        return a;
    }
}
namespace rttype{
    namespace constexprout{
        template<unsigned N=256>
        struct constexprout_t{
            char c[N]={};
            unsigned l=0;
            constexpr const char* c_str() const{return c;}
            constexpr unsigned size() const{return l;}
        };
        //template<typename T>
        //static inline constexpr rttype::constexprout_t operator<<(constexprout_t a,double b){
        //    char c[20]=rttype::out_fn::fp();
        //}
        template<unsigned N=64>
        struct ret{
            char c[N]={};
            char* p=0;
            unsigned l=0;
        };
        static constexpr char* lltoa(long long val, char* buf){
	        char* p=buf+20;
	        *p^=(*p);
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
	    static constexpr char* ulltoa(unsigned long long val, char* buf){
	        char* p=buf+20;
	        *p^=(*p);
	        do{
	            unsigned long long rem = val % 10;
	            *--p=48 | (char)rem;
	            val/=10;
	        }while(val);
	        return p;
	    }
        namespace out_fn{
        template<unsigned N=64>
        static inline constexpr ret<N> si(long long a) {
            ret<N> b{};
            char tmp[21];
            char* p = rttype::constexprout::lltoa(a, tmp);
            unsigned len=20-(p-tmp);
            for(unsigned i=0; i < len && i<N-1;i++) b.c[i]=p[i];
            b.l=len;
            return b;
        }
        
        template<unsigned N=64>
        static inline constexpr ret<N> ui(unsigned long long a) {
            ret<N> b{};
            char tmp[21];
            char* p = rttype::constexprout::ulltoa(a, tmp);
            unsigned len = 20 - (p - tmp);
            for (unsigned i = 0; i < len && i < N; i++) b.c[i] = p[i];
            b.l = len;
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> ch(char c){
            ret<N> b{};
            b.c[0]=c;
            b.l=1;
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> cp(const char* c) {
            ret<N> b{};
            b.l = 0;
            while (c[b.l] && b.l < N-1) {
                b.c[b.l] = c[b.l];
                b.l++;
            }
            if (b.l == N-1 && c[b.l]) { b.p = const_cast<char*>(c); }
            b.c[b.l] = 0;
            return b;
        }
        template<unsigned N=64,typename T>//ptr
        static inline constexpr ret<N> vp(T* a){
	        #if __cplusplus>=201103L
            ret<N> b{};
            b.c[0]='0';
            b.c[1]='x';
            unsigned long long ax=(unsigned long long)a;
            for (int i=0; i<rttype::ptr_w_rt; i++) {
			        int shift=(rttype::ptr_w_rt-1-i) <<2;
			        b.c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
			    }
			b.l=rttype::ptr_w_rt+2;
            return b;
            #else
            ret<N> b{};
            b.c[0]='0';
            b.c[1]='x';
            unsigned long long ax=(unsigned long long)a;
            for (int i=0;i<rttype::ptr_w_rt; i++) {
			        int shift=(rttype::ptr_w_rt-1-i)<<2;
			        b.c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
			}
            b.l=rttype::ptr_w_rt+2;
            return b;
            #endif
        }
        template<unsigned N=64>
        static inline constexpr ret<N> fp(long double a) {
            ret<N> b{};
            if (a == 0.0L || a == -0.0L) {
                b.c[0] = 48;//0
                b.l=1;
                return b;
            }
            unsigned idx = 0;
            if(a<0){
                b.c[idx++] = 45;//-
                a=-a;
            }
            const long double MAX_ULL = (long double)0xFFFFFFFFFFFFFFFFULL;
            if (a > MAX_ULL) {
                b.c[0] = 73;//I
                b.c[1] = 78;//N
                b.c[2] = 70;//F
                b.l=3;
                return b;
            }
            unsigned long long ip = (unsigned long long)a;
            long double frac = a - (long double)ip;
            char buf[32];
            int bi = 0;
            do {
                buf[bi++] = 48 ^ (int)(ip % 10);
                ip /= 10;
            } while (ip);
            while (bi--) b.c[idx++] = buf[bi];
            b.c[idx++] = 46;//'.'
            for (int i = 0; i < 6; i++) {
                frac *= 10;
                int digit = (int)frac;
                b.c[idx++] = 48 ^ digit;
                frac -= digit;
            }
            while (idx > 0 && b.c[idx - 1] == 48) idx--;
            if (idx > 0 && b.c[idx - 1] == 46) {//'.'
                b.c[idx++] = 48;
            }
            b.l = idx;
            return b;
        }
        }
        template<unsigned N=64>
        static inline constexpr ret<N> outf(char a){
            ret<N> b{};
            b.l=1;
            b.c[0]=a;
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> outf(float a){
            ret<N> b{};
            b=out_fn::fp<N>(a);
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> outf(double a){
            ret<N> b{};
            b=out_fn::fp<N>(a);
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> outf(long double a){
            ret<N> b{};
            b=out_fn::fp<N>(a);
            return b;
        }
        template<unsigned N=64>
        static inline constexpr ret<N> outf(bool a){
            ret<N> b{};
            b.l=1;
            if(a)
            {b.c[0]=49;}
            else{b.c[0]=48;}
            return b;
        }
        #define sifnd_rt(T) \
        template<unsigned N=64>\
        static inline constexpr ret<N> outf(T a){\
            ret<N> b{};\
            b=out_fn::si<N>((long long)a);\
            return b;\
        }
        ;
        sifnd_rt(short);
        sifnd_rt(int);
        sifnd_rt(long);
        sifnd_rt(long long);
        #define uifnd_rt(T) \
        template<unsigned N=64>\
        static inline constexpr ret<N> outf(T a){\
            ret<N> b{};\
            b=out_fn::ui<N>((unsigned long long)a);\
            return b;\
        }
        uifnd_rt(unsigned short);
        uifnd_rt(unsigned);
        uifnd_rt(unsigned long);
        uifnd_rt(unsigned long long);
        #undef uifnd_rt
        template<unsigned N=64,typename T>
        static inline constexpr ret<N> outf(T* a){
            ret<N> b{};
            b=out_fn::vp<N>(a);
            return b;
        }
        template<unsigned N=64,typename T>
        static inline constexpr ret<N> outf(T a) {
            ret<N> b{};
            if(rth_io::is_integer<T>::v){
                if(rth_io::is_unsigned_integer<T>::v){
                    b=out_fn::ui<N>(a);
                }else{
                    b=out_fn::si<N>(a);
                }
            }else if(rth_io::is_charptr<T>::v){
                b=out_fn::cp<N>(a);
            }else{
                b=out_fn::si<N>(int(a));
            }
            return b;
        }
#define fdf_rt(T) template<unsigned N>\
    static inline constexpr constexprout_t<N> operator<<(constexprout_t<N> a, T b) {\
        ret<N> r = outf<N>(b);\
        unsigned i = 0;\
        for (; i < r.l && (a.l + i) < N - 1; i++)\
        { a.c[a.l + i] = r.c[i]; }\
        a.l += i;\
        a.c[a.l] = 0;\
        return a;\
    }
        fdf_rt(double);
        fdf_rt(float);
        fdf_rt(long double);
        fdf_rt(int);
        fdf_rt(unsigned);
        fdf_rt(long);
        fdf_rt(short);
        fdf_rt(unsigned short);
        fdf_rt(long long);
        fdf_rt(unsigned long long);
        fdf_rt(char);
        fdf_rt(signed char);
        fdf_rt(unsigned char);
        fdf_rt(bool);
        #undef fdf_rt
        template<unsigned N>
        static inline constexpr constexprout_t<N> operator<<(constexprout_t<N> a, const char* s) {
            unsigned i = 0;
            while (s[i] && (a.l + i) < N - 1) {
                a.c[a.l + i] = s[i];
                i++;
            }
            a.l+=i;
            a.c[a.l]=0;
            return a;
        }
        template<unsigned N,typename T>
        static inline constexpr constexprout_t<N> operator<<(constexprout_t<N> a,T b){//bug
            ret<N> r=outf<N>(b);
            unsigned i=0;
            if(r.p){
                while(i<r.l && (a.l+i)<N-1) {
                    a.c[a.l+i]=r.c[i];
                    i++;
                }
                a.l+=i;
                unsigned j = 0;
                while(r.p[j] && (a.l+j)<N-1) {
                    a.c[a.l+j]=r.p[j];
                    j++;
                }
                a.l+=j;
                a.c[a.l]='\0';
                return a;
            }
            for(;i<r.l && (a.l+i)<N-1;i++){
                a.c[a.l+i]=r.c[i];
            }
            a.l+=i;
            a.c[a.l]=0;
            return a;
        }
    }
}

namespace rttype{
    namespace fastout{
        template<unsigned N=256>
        struct fastout_t{
            char c[N]={};
            unsigned l=0;
        };
        template<unsigned N=64>
        struct ret{
            char c[N]={};
            char* p=0;
            unsigned l=0;
        };
        struct out{};
        struct outc{};
        namespace out_fn{
            template<unsigned N=64>
            static inline ret<N> si(long long a) {
                ret<N> b{};
                char tmp[21];
                char* p = rth_io::lltoa(a, tmp);
                unsigned len = 0;
                while (p[len]) len++;
                for (unsigned i = 0; i < len && i < N; i++) {
                    b.c[i] = p[i];
                }
                b.l = len;
                return b;
            }
            template<unsigned N=64>
            static inline ret<N> ui(unsigned long long a) {
                ret<N> b{};
                char tmp[21];
                char* p = rth_io::ulltoa(a, tmp);
                unsigned len = 0;
                while (p[len]) len++;
                for (unsigned i = 0; i < len && i < N; i++) {
                    b.c[i] = p[i];
                }
                b.l = len;
                return b;
            }
            template<unsigned N=64>
            static inline ret<N> ch(char c){
                ret<N> b{};
                b.c[0]=c;
                b.l=1;
                return b;
            }
            template<unsigned N=64>
            static inline ret<N> cp(const char* c) {
                ret<N> b{};
                b.l=0;
                while (c[b.l] && b.l < N-1) {
                    b.c[b.l] = c[b.l];
                    b.l++;
                }
                if(b.l==N-1 && c[b.l]){b.p=const_cast<char*>(c);}
                b.c[b.l]=0;
                return b;
            }
            template<unsigned N=64,typename T>
            static inline ret<N> vp(T* a){
                ret<N> b{};
                b.c[0]='0';
                b.c[1]='x';
                unsigned long long ax=(unsigned long long)a;
                for (int i=0; i<rttype::ptr_w_rt; i++) {
                    int shift=(rttype::ptr_w_rt-1-i) <<2;
                    b.c[2+i]=rttype::hexlist[(ax>>shift)&0xF];
                }
                b.l=rttype::ptr_w_rt+2;
                return b;
            }
            template<unsigned N=64>
            static inline ret<N> fp(long double a) {
                ret<N> b{};
                if (a == 0.0L || a == -0.0L) {
                    b.c[0] = 48;//0
                    b.l=1;
                    return b;
                }
                unsigned idx = 0;
                if(a<0){
                    b.c[idx++] = 45;//-
                    a=-a;
                }
                const long double MAX_ULL = (long double)0xFFFFFFFFFFFFFFFFULL;
                if (a > MAX_ULL) {
                    b.c[0] = 73;//I
                    b.c[1] = 78;//N
                    b.c[2] = 70;//F
                    b.l=3;
                    return b;
                }
                unsigned long long ip = (unsigned long long)a;
                long double frac = a - (long double)ip;
                char buf[32];
                int bi = 0;
                do {
                    buf[bi++] = 48 ^ (int)(ip % 10);
                    ip /= 10;
                } while (ip);
                while (bi--) b.c[idx++] = buf[bi];
                b.c[idx++] = 46;//'.'
                for (int i = 0; i < 6; i++) {
                    frac *= 10;
                    int digit = (int)frac;
                    b.c[idx++] = 48 ^ digit;
                    frac -= digit;
                }
                while (idx > 0 && b.c[idx - 1] == 48) idx--;
                if (idx > 0 && b.c[idx - 1] == 46) {//'.'
                    b.c[idx++] = 48;
                }
                b.l = idx;
                return b;
            }
        }
        template<unsigned N=64>
        static inline ret<N> outf(char a){
            ret<N> b{};
            b.l=1;
            b.c[0]=a;
            return b;
        }
        template<unsigned N=64>
        static inline ret<N> outf(float a){
            return out_fn::fp<N>(a);
        }
        template<unsigned N=64>
        static inline ret<N> outf(double a){
            return out_fn::fp<N>(a);
        }
        template<unsigned N=64>
        static inline ret<N> outf(long double a){
            return out_fn::fp<N>(a);
        }
        template<unsigned N=64>
        static inline ret<N> outf(bool a){
            ret<N> b{};
            b.l=1;
            b.c[0]=a?49:48;
            return b;
        }
        #define sifnd_rt(T) \
        template<unsigned N=64>\
        static inline ret<N> outf(T a){\
            ret<N> b{};\
            b=out_fn::si<N>((long long)a);\
            return b;\
        }
        ;
        sifnd_rt(short);
        sifnd_rt(int);
        sifnd_rt(long);
        sifnd_rt(long long);
        #define uifnd_rt(T) \
        template<unsigned N=64>\
        static inline ret<N> outf(T a){\
            ret<N> b{};\
            b=out_fn::ui<N>((unsigned long long)a);\
            return b;\
        }
        uifnd_rt(unsigned short);
        uifnd_rt(unsigned);
        uifnd_rt(unsigned long);
        uifnd_rt(unsigned long long);
        #undef uifnd_rt
        template<unsigned N=64,typename T>
        static inline ret<N> outf(T* a){
            return out_fn::vp<N>(a);
        }
        template<unsigned N=64,typename T>
        static inline ret<N> outf(T a) {
            ret<N> b{};
            if(rth_io::is_integer<T>::v){
                if(rth_io::is_unsigned_integer<T>::v){
                    b=out_fn::ui<N>(a);
                }else{
                    b=out_fn::si<N>(a);
                }
            }else if(rth_io::is_charptr<T>::v){
                b=out_fn::cp<N>(a);
            }else{
                b=out_fn::si<N>(int(a));
            }
            return b;
        }
#define fdf_rt(T) template<unsigned N>\
    static inline fastout_t<N> operator<<(fastout_t<N> a, T b) {\
        ret<N> r = outf<N>(b);\
        unsigned i = 0;\
        for (; i < r.l && (a.l + i) < N - 1; i++)\
        { a.c[a.l + i] = r.c[i]; }\
        a.l += i;\
        a.c[a.l] = 0;\
        return a;\
    }
        fdf_rt(double);
        fdf_rt(float);
        fdf_rt(long double);
        //fdf_rt(int);
        fdf_rt(unsigned);
        fdf_rt(long);
        fdf_rt(short);
        fdf_rt(unsigned short);
        fdf_rt(long long);
        fdf_rt(unsigned long long);
        fdf_rt(char);
        fdf_rt(signed char);
        fdf_rt(unsigned char);
        fdf_rt(bool);
        #undef fdf_rt
        template<unsigned N>
        static inline fastout_t<N> operator<<(fastout_t<N> a, rttype::fastout::out b){
            writer(a.c,a.l);
            return a;
        }
        template<unsigned N>
        static inline fastout_t<N> operator<<(fastout_t<N> a, rttype::fastout::outc b){
            writer(a.c,a.l);
            return {};
        }
        template<unsigned N=64>
        static inline fastout_t<N> operator<<(fastout_t<N> a, const char* s) {
            unsigned i = 0;
            while (s[i] && (a.l + i) < N - 1) {
                a.c[a.l + i] = s[i];
                i++;
            }
            a.l+=i;
            a.c[a.l]=0;
            return a;
        }
        template<unsigned N,typename T>
        static inline fastout_t<N> operator<<(fastout_t<N> a, T b){
            ret<N> r=outf<N>(b);
            unsigned i=0;
            if(r.p){
                while(i<r.l && (a.l+i)<N-1) {
                    a.c[a.l+i]=r.c[i];
                    i++;
                }
                a.l+=i;
                unsigned j = 0;
                while(r.p[j] && (a.l+j)<N-1) {
                    a.c[a.l+j]=r.p[j];
                    j++;
                }
                a.l+=j;
                a.c[a.l]='\0';
                return a;
            }
            for(;i<r.l && (a.l+i)<N-1;i++){
                a.c[a.l+i]=r.c[i];
            }
            a.l+=i;
            a.c[a.l]=0;
            return a;
        }
        //
    }
}
#endif
#endif/**/
