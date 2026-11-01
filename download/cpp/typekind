/* typekind */
#ifndef typekind_rt
#define typekind_rt

/* inline_rt */
#if defined(__STDC_HOSTED__) && __STDC_HOSTED__
    #if defined(_MSC_VER)
        #define inline_rt __forceinline
    #elif defined(__GNUC__) || defined(__clang__)
        #define inline_rt __attribute__((always_inline)) inline
    #elif defined(__INTEL_COMPILER) || defined(__ICC)
        #define inline_rt __forceinline
    #elif defined(__DMC__) || defined(_DIGITAL_MARS)
        #define inline_rt __inline
    #else
        #define inline_rt inline
    #endif
#else
    #define inline_rt inline
#endif
namespace{
    namespace rangtt{
        /* basic type:enum */
        enum class type_enum{
            vd=0,
            sc,ss,si,sl,sll, /*   signed  */
            uc,us,ui,ul,ull, /*  unsigned */
            ch,bo,           /* char,bool */
            fl,db,ld,        /*   float   */

            /* ptr */
            vdp,scp,ssp,sip,slp,sllp,
            ucp,usp,uip,ulp,ullp,
            chp,bop,
            flp,dbp,ldp,

            fnp, /* function pointer */
            mfp, /* member function pointer */
            mdp, /* member data pointer */

            /* array */
            sca,ssa,sia,sla,slla,
            uca,usa,uia,ula,ulla,
            cha,boa,
            fla,dba,lda,

            vdpa,scpa,sspa,sipa,slpa,sllpa,
            ucpa,uspa,uipa,ulpa,ullpa,
            chpa,bopa,
            ptra,
            flpa,dbpa,ldpa,

            unknown=-1
        };
        /* basic type */
        type_enum inline_rt typekind(void)                { return type_enum::vd;  }
        type_enum inline_rt typekind(signed char)         { return type_enum::sc;  }
        type_enum inline_rt typekind(short)               { return type_enum::ss;  }
        type_enum inline_rt typekind(int)                 { return type_enum::si;  }
        type_enum inline_rt typekind(long)                { return type_enum::sl;  }
        type_enum inline_rt typekind(long long)           { return type_enum::sll; }
        type_enum inline_rt typekind(unsigned char)       { return type_enum::uc;  }
        type_enum inline_rt typekind(unsigned short)      { return type_enum::us;  }
        type_enum inline_rt typekind(unsigned int)        { return type_enum::ui;  }
        type_enum inline_rt typekind(unsigned long)       { return type_enum::ul;  }
        type_enum inline_rt typekind(unsigned long long)  { return type_enum::ull; }
        type_enum inline_rt typekind(bool)                { return type_enum::bo;  }
        type_enum inline_rt typekind(char)                { return type_enum::ch;  }
        type_enum inline_rt typekind(float)               { return type_enum::fl;  }
        type_enum inline_rt typekind(double)              { return type_enum::db;  }
        type_enum inline_rt typekind(long double)         { return type_enum::ld;  }
        
        type_enum inline_rt typekind(void*)               { return type_enum::vdp; }
        type_enum inline_rt typekind(signed char*)        { return type_enum::scp; }
        type_enum inline_rt typekind(short*)              { return type_enum::ssp; }
        type_enum inline_rt typekind(int*)                { return type_enum::sip; }
        type_enum inline_rt typekind(long*)               { return type_enum::slp; }
        type_enum inline_rt typekind(long long*)          { return type_enum::sllp;}
        type_enum inline_rt typekind(unsigned char*)      { return type_enum::ucp; }
        type_enum inline_rt typekind(unsigned short*)     { return type_enum::usp; }
        type_enum inline_rt typekind(unsigned int*)       { return type_enum::uip; }
        type_enum inline_rt typekind(unsigned long*)      { return type_enum::ulp; }
        type_enum inline_rt typekind(unsigned long long*) { return type_enum::ullp;}
        type_enum inline_rt typekind(bool*)               { return type_enum::bop; }
        type_enum inline_rt typekind(char*)               { return type_enum::chp; }
        type_enum inline_rt typekind(float*)              { return type_enum::flp; }
        type_enum inline_rt typekind(double*)             { return type_enum::dbp; }
        type_enum inline_rt typekind(long double*)        { return type_enum::ldp; }
        /* nullptr */
        #if __cplusplus>=201103L
        type_enum inline_rt typekind(decltype(nullptr))   { return type_enum::vdp; }
        #endif
        /* remove "const" and "volatile" */
        #ifndef use_rm_cv_rt
        #define use_rm_cv_rt
        template<typename T>
        struct rm_cv{using t=T;};
        template<typename T>
        struct rm_cv<const T>{using t=T;};
        template<typename T>
        struct rm_cv<volatile T>{using t=T;};
        template<typename T>
        struct rm_cv<const volatile T>{using t=T;};
        
        #endif
        /* is_same */
        #ifndef use_is_same_rt
        #define use_is_same_rt
        template<typename T,typename U>
        struct is_same{static const int v=0;};
        template<typename T>
        struct is_same<T,T>{static const int v=1;};
        #endif
        /* function pointer */
        template<typename R, typename... Args>
        type_enum inline_rt typekind(R(*)(Args...))               { return type_enum::fnp; }

        template<typename R, typename... Args>
        type_enum inline_rt typekind(R(*)(Args..., ...))          { return type_enum::fnp; }

        #if __cplusplus >= 201703L
        template<typename R, typename... Args>
        type_enum inline_rt typekind(R(*)(Args...) noexcept)      { return type_enum::fnp; }

        template<typename R, typename... Args>
        type_enum inline_rt typekind(R(*)(Args..., ...) noexcept) { return type_enum::fnp; }
        #endif

        /* member function pointer: mfp */

        /* no ref ,no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...))                     { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const)               { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile)            { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile)      { return type_enum::mfp; }

        /* & ,no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) &)                   { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const &)             { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile &)          { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile &)    { return type_enum::mfp; }

        /* && , no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) &&)                  { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const &&)            { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile &&)         { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile &&)   { return type_enum::mfp; }

        #if __cplusplus >= 201703L
        /* ref, noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) noexcept)                    { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const noexcept)              { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile noexcept)           { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile noexcept)     { return type_enum::mfp; }

        /* & ,noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) & noexcept)                  { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const & noexcept)            { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile & noexcept)         { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile & noexcept)   { return type_enum::mfp; }

        /* &&,noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) && noexcept)                 { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const && noexcept)           { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) volatile && noexcept)        { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args...) const volatile && noexcept)  { return type_enum::mfp; }
        #endif

        /* C-style variadic member function pointer */

        /* no ref, no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...))                    { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const)              { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile)           { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile)     { return type_enum::mfp; }

        /* &, no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) &)                  { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const &)            { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile &)         { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile &)   { return type_enum::mfp; }

        /* &&, no noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) &&)                 { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const &&)           { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile &&)        { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile &&)  { return type_enum::mfp; }

        #if __cplusplus >= 201703L
        /* no ref, noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) noexcept)                   { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const noexcept)             { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile noexcept)          { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile noexcept)    { return type_enum::mfp; }

        /* &, noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) & noexcept)                 { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const & noexcept)           { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile & noexcept)        { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile & noexcept)  { return type_enum::mfp; }

        /* &&, noexcept */
        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) && noexcept)                { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const && noexcept)          { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) volatile && noexcept)       { return type_enum::mfp; }

        template<typename C, typename R, typename... Args>
        type_enum inline_rt typekind(R(C::*)(Args..., ...) const volatile && noexcept) { return type_enum::mfp; }
        #endif

        /* member data ptr*/
        template<typename C, typename R>
        type_enum inline_rt typekind(R C::*) { return type_enum::mdp; }

        /* array */
        using len_t=decltype(sizeof(0));
        template<len_t N> type_enum inline_rt typekind(signed char        (&)[N]) {return type_enum::sca; }
        template<len_t N> type_enum inline_rt typekind(short              (&)[N]) {return type_enum::ssa; }
        template<len_t N> type_enum inline_rt typekind(int                (&)[N]) {return type_enum::sia; }
        template<len_t N> type_enum inline_rt typekind(long               (&)[N]) {return type_enum::sla; }
        template<len_t N> type_enum inline_rt typekind(long long          (&)[N]) {return type_enum::slla;}
        template<len_t N> type_enum inline_rt typekind(unsigned char      (&)[N]) {return type_enum::uca; }
        template<len_t N> type_enum inline_rt typekind(unsigned short     (&)[N]) {return type_enum::usa; }
        template<len_t N> type_enum inline_rt typekind(unsigned int       (&)[N]) {return type_enum::uia; }
        template<len_t N> type_enum inline_rt typekind(unsigned long      (&)[N]) {return type_enum::ula; }
        template<len_t N> type_enum inline_rt typekind(unsigned long long (&)[N]) {return type_enum::ulla;}
        template<len_t N> type_enum inline_rt typekind(char               (&)[N]) {return type_enum::cha; }
        template<len_t N> type_enum inline_rt typekind(bool               (&)[N]) {return type_enum::boa; }
        template<len_t N> type_enum inline_rt typekind(float              (&)[N]) {return type_enum::fla; }
        template<len_t N> type_enum inline_rt typekind(double             (&)[N]) {return type_enum::dba; }
        template<len_t N> type_enum inline_rt typekind(long double        (&)[N]) {return type_enum::lda; }

        template<len_t N> type_enum inline_rt typekind(void*              (&)[N]) {return type_enum::vdpa; }
        template<len_t N> type_enum inline_rt typekind(signed char*       (&)[N]) {return type_enum::scpa; }
        template<len_t N> type_enum inline_rt typekind(short*             (&)[N]) {return type_enum::sspa; }
        template<len_t N> type_enum inline_rt typekind(int*               (&)[N]) {return type_enum::sipa; }
        template<len_t N> type_enum inline_rt typekind(long*              (&)[N]) {return type_enum::slpa; }
        template<len_t N> type_enum inline_rt typekind(long long*         (&)[N]) {return type_enum::sllpa;}
        template<len_t N> type_enum inline_rt typekind(unsigned char*     (&)[N]) {return type_enum::ucpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned short*    (&)[N]) {return type_enum::uspa; }
        template<len_t N> type_enum inline_rt typekind(unsigned int*      (&)[N]) {return type_enum::uipa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long*     (&)[N]) {return type_enum::ulpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long long*(&)[N]) {return type_enum::ullpa;}
        template<len_t N> type_enum inline_rt typekind(char*              (&)[N]) {return type_enum::chpa; }
        template<len_t N> type_enum inline_rt typekind(bool*              (&)[N]) {return type_enum::bopa; }
        template<len_t N> type_enum inline_rt typekind(float*             (&)[N]) {return type_enum::flpa; }
        template<len_t N> type_enum inline_rt typekind(double*            (&)[N]) {return type_enum::dbpa; }
        template<len_t N> type_enum inline_rt typekind(long double*       (&)[N]) {return type_enum::ldpa; }
        
        template<len_t N> type_enum inline_rt typekind(const signed char        (&)[N]) {return type_enum::sca; }
        template<len_t N> type_enum inline_rt typekind(const short              (&)[N]) {return type_enum::ssa; }
        template<len_t N> type_enum inline_rt typekind(const int                (&)[N]) {return type_enum::sia; }
        template<len_t N> type_enum inline_rt typekind(const long               (&)[N]) {return type_enum::sla; }
        template<len_t N> type_enum inline_rt typekind(const long long          (&)[N]) {return type_enum::slla;}
        template<len_t N> type_enum inline_rt typekind(const unsigned char      (&)[N]) {return type_enum::uca; }
        template<len_t N> type_enum inline_rt typekind(const unsigned short     (&)[N]) {return type_enum::usa; }
        template<len_t N> type_enum inline_rt typekind(const unsigned int       (&)[N]) {return type_enum::uia; }
        template<len_t N> type_enum inline_rt typekind(const unsigned long      (&)[N]) {return type_enum::ula; }
        template<len_t N> type_enum inline_rt typekind(const unsigned long long (&)[N]) {return type_enum::ulla;}
        template<len_t N> type_enum inline_rt typekind(const char               (&)[N]) {return type_enum::cha; }
        template<len_t N> type_enum inline_rt typekind(const bool               (&)[N]) {return type_enum::boa; }
        template<len_t N> type_enum inline_rt typekind(const float              (&)[N]) {return type_enum::fla; }
        template<len_t N> type_enum inline_rt typekind(const double             (&)[N]) {return type_enum::dba; }
        template<len_t N> type_enum inline_rt typekind(const long double        (&)[N]) {return type_enum::lda; }

        template<len_t N> type_enum inline_rt typekind(void*               const (&)[N]) {return type_enum::vdpa; }
        template<len_t N> type_enum inline_rt typekind(signed char*        const (&)[N]) {return type_enum::scpa; }
        template<len_t N> type_enum inline_rt typekind(short*              const (&)[N]) {return type_enum::sspa; }
        template<len_t N> type_enum inline_rt typekind(int*                const (&)[N]) {return type_enum::sipa; }
        template<len_t N> type_enum inline_rt typekind(long*               const (&)[N]) {return type_enum::slpa; }
        template<len_t N> type_enum inline_rt typekind(long long*          const (&)[N]) {return type_enum::sllpa;}
        template<len_t N> type_enum inline_rt typekind(unsigned char*      const (&)[N]) {return type_enum::ucpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned short*     const (&)[N]) {return type_enum::uspa; }
        template<len_t N> type_enum inline_rt typekind(unsigned int*       const (&)[N]) {return type_enum::uipa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long*      const (&)[N]) {return type_enum::ulpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long long* const (&)[N]) {return type_enum::ullpa;}
        template<len_t N> type_enum inline_rt typekind(char*               const (&)[N]) {return type_enum::chpa; }
        template<len_t N> type_enum inline_rt typekind(bool*               const (&)[N]) {return type_enum::bopa; }
        template<len_t N> type_enum inline_rt typekind(float*              const (&)[N]) {return type_enum::flpa; }
        template<len_t N> type_enum inline_rt typekind(double*             const (&)[N]) {return type_enum::dbpa; }
        template<len_t N> type_enum inline_rt typekind(long double*        const (&)[N]) {return type_enum::ldpa; }

        template<len_t N> type_enum inline_rt typekind(volatile signed char        (&)[N]) {return type_enum::sca; }
        template<len_t N> type_enum inline_rt typekind(volatile short              (&)[N]) {return type_enum::ssa; }
        template<len_t N> type_enum inline_rt typekind(volatile int                (&)[N]) {return type_enum::sia; }
        template<len_t N> type_enum inline_rt typekind(volatile long               (&)[N]) {return type_enum::sla; }
        template<len_t N> type_enum inline_rt typekind(volatile long long          (&)[N]) {return type_enum::slla;}
        template<len_t N> type_enum inline_rt typekind(volatile unsigned char      (&)[N]) {return type_enum::uca; }
        template<len_t N> type_enum inline_rt typekind(volatile unsigned short     (&)[N]) {return type_enum::usa; }
        template<len_t N> type_enum inline_rt typekind(volatile unsigned int       (&)[N]) {return type_enum::uia; }
        template<len_t N> type_enum inline_rt typekind(volatile unsigned long      (&)[N]) {return type_enum::ula; }
        template<len_t N> type_enum inline_rt typekind(volatile unsigned long long (&)[N]) {return type_enum::ulla;}
        template<len_t N> type_enum inline_rt typekind(volatile char               (&)[N]) {return type_enum::cha; }
        template<len_t N> type_enum inline_rt typekind(volatile bool               (&)[N]) {return type_enum::boa; }
        template<len_t N> type_enum inline_rt typekind(volatile float              (&)[N]) {return type_enum::fla; }
        template<len_t N> type_enum inline_rt typekind(volatile double             (&)[N]) {return type_enum::dba; }
        template<len_t N> type_enum inline_rt typekind(volatile long double        (&)[N]) {return type_enum::lda; }

        template<len_t N> type_enum inline_rt typekind(void*               volatile (&)[N]) {return type_enum::vdpa; }
        template<len_t N> type_enum inline_rt typekind(signed char*        volatile (&)[N]) {return type_enum::scpa; }
        template<len_t N> type_enum inline_rt typekind(short*              volatile (&)[N]) {return type_enum::sspa; }
        template<len_t N> type_enum inline_rt typekind(int*                volatile (&)[N]) {return type_enum::sipa; }
        template<len_t N> type_enum inline_rt typekind(long*               volatile (&)[N]) {return type_enum::slpa; }
        template<len_t N> type_enum inline_rt typekind(long long*          volatile (&)[N]) {return type_enum::sllpa;}
        template<len_t N> type_enum inline_rt typekind(unsigned char*      volatile (&)[N]) {return type_enum::ucpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned short*     volatile (&)[N]) {return type_enum::uspa; }
        template<len_t N> type_enum inline_rt typekind(unsigned int*       volatile (&)[N]) {return type_enum::uipa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long*      volatile (&)[N]) {return type_enum::ulpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long long* volatile (&)[N]) {return type_enum::ullpa;}
        template<len_t N> type_enum inline_rt typekind(char*               volatile (&)[N]) {return type_enum::chpa; }
        template<len_t N> type_enum inline_rt typekind(bool*               volatile (&)[N]) {return type_enum::bopa; }
        template<len_t N> type_enum inline_rt typekind(float*              volatile (&)[N]) {return type_enum::flpa; }
        template<len_t N> type_enum inline_rt typekind(double*             volatile (&)[N]) {return type_enum::dbpa; }
        template<len_t N> type_enum inline_rt typekind(long double*        volatile (&)[N]) {return type_enum::ldpa; }

        template<len_t N> type_enum inline_rt typekind(const volatile signed char        (&)[N]) {return type_enum::sca; }
        template<len_t N> type_enum inline_rt typekind(const volatile short              (&)[N]) {return type_enum::ssa; }
        template<len_t N> type_enum inline_rt typekind(const volatile int                (&)[N]) {return type_enum::sia; }
        template<len_t N> type_enum inline_rt typekind(const volatile long               (&)[N]) {return type_enum::sla; }
        template<len_t N> type_enum inline_rt typekind(const volatile long long          (&)[N]) {return type_enum::slla;}
        template<len_t N> type_enum inline_rt typekind(const volatile unsigned char      (&)[N]) {return type_enum::uca; }
        template<len_t N> type_enum inline_rt typekind(const volatile unsigned short     (&)[N]) {return type_enum::usa; }
        template<len_t N> type_enum inline_rt typekind(const volatile unsigned int       (&)[N]) {return type_enum::uia; }
        template<len_t N> type_enum inline_rt typekind(const volatile unsigned long      (&)[N]) {return type_enum::ula; }
        template<len_t N> type_enum inline_rt typekind(const volatile unsigned long long (&)[N]) {return type_enum::ulla;}
        template<len_t N> type_enum inline_rt typekind(const volatile char               (&)[N]) {return type_enum::cha; }
        template<len_t N> type_enum inline_rt typekind(const volatile bool               (&)[N]) {return type_enum::boa; }
        template<len_t N> type_enum inline_rt typekind(const volatile float              (&)[N]) {return type_enum::fla; }
        template<len_t N> type_enum inline_rt typekind(const volatile double             (&)[N]) {return type_enum::dba; }
        template<len_t N> type_enum inline_rt typekind(const volatile long double        (&)[N]) {return type_enum::lda; }

        template<len_t N> type_enum inline_rt typekind(void*               const volatile(&)[N]) {return type_enum::vdpa; }
        template<len_t N> type_enum inline_rt typekind(signed char*        const volatile(&)[N]) {return type_enum::scpa; }
        template<len_t N> type_enum inline_rt typekind(short*              const volatile(&)[N]) {return type_enum::sspa; }
        template<len_t N> type_enum inline_rt typekind(int*                const volatile(&)[N]) {return type_enum::sipa; }
        template<len_t N> type_enum inline_rt typekind(long*               const volatile(&)[N]) {return type_enum::slpa; }
        template<len_t N> type_enum inline_rt typekind(long long*          const volatile(&)[N]) {return type_enum::sllpa;}
        template<len_t N> type_enum inline_rt typekind(unsigned char*      const volatile(&)[N]) {return type_enum::ucpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned short*     const volatile(&)[N]) {return type_enum::uspa; }
        template<len_t N> type_enum inline_rt typekind(unsigned int*       const volatile(&)[N]) {return type_enum::uipa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long*      const volatile(&)[N]) {return type_enum::ulpa; }
        template<len_t N> type_enum inline_rt typekind(unsigned long long* const volatile(&)[N]) {return type_enum::ullpa;}
        template<len_t N> type_enum inline_rt typekind(char*               const volatile(&)[N]) {return type_enum::chpa; }
        template<len_t N> type_enum inline_rt typekind(bool*               const volatile(&)[N]) {return type_enum::bopa; }
        template<len_t N> type_enum inline_rt typekind(float*              const volatile(&)[N]) {return type_enum::flpa; }
        template<len_t N> type_enum inline_rt typekind(double*             const volatile(&)[N]) {return type_enum::dbpa; }
        template<len_t N> type_enum inline_rt typekind(long double*        const volatile(&)[N]) {return type_enum::ldpa;}
        /* is_arr (Removable)*/
        /* 
          If you need, please change "#if 0" to "#if 1"
        */
        #if 0
        template<typename T>         struct [[deprecated]] is_arr      {static constexpr len_t v=0;};
        template<typename T,len_t N> struct [[deprecated]] is_arr<T[N]>{static constexpr len_t v=1+is_arr<T>::v;};
        #endif
        template<typename T>         struct rm_arr             {static constexpr type_enum v=type_enum::unknown;};
        template<typename T,len_t N> struct rm_arr<T*[N]>      { static constexpr type_enum v = type_enum::ptra;};
        template<len_t N> struct rm_arr<signed char[N]>        { static constexpr type_enum v = type_enum::sca; };
        template<len_t N> struct rm_arr<short[N]>              { static constexpr type_enum v = type_enum::ssa; };
        template<len_t N> struct rm_arr<int[N]>                { static constexpr type_enum v = type_enum::sia; };
        template<len_t N> struct rm_arr<long[N]>               { static constexpr type_enum v = type_enum::sla; };
        template<len_t N> struct rm_arr<long long[N]>          { static constexpr type_enum v = type_enum::slla;};
        template<len_t N> struct rm_arr<unsigned char[N]>      { static constexpr type_enum v = type_enum::uca; };
        template<len_t N> struct rm_arr<unsigned short[N]>     { static constexpr type_enum v = type_enum::usa; };
        template<len_t N> struct rm_arr<unsigned int[N]>       { static constexpr type_enum v = type_enum::uia; };
        template<len_t N> struct rm_arr<unsigned long[N]>      { static constexpr type_enum v = type_enum::ula; };
        template<len_t N> struct rm_arr<unsigned long long[N]> { static constexpr type_enum v = type_enum::ulla;};
        template<len_t N> struct rm_arr<char[N]>               { static constexpr type_enum v = type_enum::cha; };
        template<len_t N> struct rm_arr<bool[N]>               { static constexpr type_enum v = type_enum::boa; };
        template<len_t N> struct rm_arr<float[N]>              { static constexpr type_enum v = type_enum::fla; };
        template<len_t N> struct rm_arr<double[N]>             { static constexpr type_enum v = type_enum::dba; };
        template<len_t N> struct rm_arr<long double[N]>        { static constexpr type_enum v = type_enum::lda; };
        template<len_t N> struct rm_arr<void*[N]>               {static constexpr type_enum v = type_enum::vdpa; };
        template<len_t N> struct rm_arr<signed char*[N]>        {static constexpr type_enum v = type_enum::scpa; };
        template<len_t N> struct rm_arr<short*[N]>              {static constexpr type_enum v = type_enum::sspa; };
        template<len_t N> struct rm_arr<int*[N]>                {static constexpr type_enum v = type_enum::sipa; };
        template<len_t N> struct rm_arr<long*[N]>               {static constexpr type_enum v = type_enum::slpa; };
        template<len_t N> struct rm_arr<long long*[N]>          {static constexpr type_enum v = type_enum::sllpa;};
        template<len_t N> struct rm_arr<unsigned char*[N]>      {static constexpr type_enum v = type_enum::ucpa; };
        template<len_t N> struct rm_arr<unsigned short*[N]>     {static constexpr type_enum v = type_enum::uspa; };
        template<len_t N> struct rm_arr<unsigned int*[N]>       {static constexpr type_enum v = type_enum::uipa; };
        template<len_t N> struct rm_arr<unsigned long*[N]>      {static constexpr type_enum v = type_enum::ulpa; };
        template<len_t N> struct rm_arr<unsigned long long*[N]> {static constexpr type_enum v = type_enum::ullpa;};
        template<len_t N> struct rm_arr<char*[N]>               {static constexpr type_enum v = type_enum::chpa; };
        template<len_t N> struct rm_arr<bool*[N]>               {static constexpr type_enum v = type_enum::bopa; };
        template<len_t N> struct rm_arr<float*[N]>              {static constexpr type_enum v = type_enum::flpa; };
        template<len_t N> struct rm_arr<double*[N]>             {static constexpr type_enum v = type_enum::dbpa; };
        template<len_t N> struct rm_arr<long double*[N]>        {static constexpr type_enum v = type_enum::ldpa; };
        template<typename E, len_t M, len_t N>
        struct rm_arr<E[M][N]> { static constexpr type_enum v=rm_arr<E[M]>::v; };
        template<typename T, len_t N>
        type_enum inline_rt typekind(T (&)[N]) {
            using U = typename rm_cv<T>::t;
            return rm_arr<U[N]>::v;
        }

        /* fallback */
        template<typename T>
        type_enum inline_rt typekind(T)  {
            using U=typename rm_cv<T>::t;
            if(!(is_same<T,U>::v))
                return typekind(U());
            return type_enum::unknown;
                                         }
        /* ptr */
        template <typename T>
        type_enum inline_rt typekind(const T*)          { return typekind(static_cast<T*>(0)); }
        template <typename T>
        type_enum inline_rt typekind(volatile T*)       { return typekind(static_cast<T*>(0)); }
        template <typename T>
        type_enum inline_rt typekind(const volatile T*) { return typekind(static_cast<T*>(0)); }
    }
}
#endif
/*
 * include:
 *     basic type
 *     basic pointer type
 *     function pointer
 *     member function pointer
 *     member data pointer
 *     array
 *     pointer array
 *     more array
 * 
 * type_enum typekind(void){...} -> typekind()
 * Fails for non-default-constructible classes.(fallback)
 * typekind("hi") -> cha
 * is_arr is unused
 */
/*
 ____      _    _   _  ____ _____ _____ 
|  _ \    / \  | \ | |/ ___|_   _|_   _|
| |_) |  / _ \ |  \| | |  _  | |   | |  
|  _ <  / ___ \| |\  | |_| | | |   | |  
|_| \_\/_/   \_\_| \_|\____| |_|   |_|  

*/
