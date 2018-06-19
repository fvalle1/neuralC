// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__XRayMachine

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/Users/filippo/Developer/neuralC/XRayMachine/XRayMachine.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *XRayMachine_Dictionary();
   static void XRayMachine_TClassManip(TClass*);
   static void delete_XRayMachine(void *p);
   static void deleteArray_XRayMachine(void *p);
   static void destruct_XRayMachine(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::XRayMachine*)
   {
      ::XRayMachine *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::XRayMachine));
      static ::ROOT::TGenericClassInfo 
         instance("XRayMachine", "XRayMachine/XRayMachine.h", 15,
                  typeid(::XRayMachine), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &XRayMachine_Dictionary, isa_proxy, 0,
                  sizeof(::XRayMachine) );
      instance.SetDelete(&delete_XRayMachine);
      instance.SetDeleteArray(&deleteArray_XRayMachine);
      instance.SetDestructor(&destruct_XRayMachine);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::XRayMachine*)
   {
      return GenerateInitInstanceLocal((::XRayMachine*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::XRayMachine*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *XRayMachine_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::XRayMachine*)0x0)->GetClass();
      XRayMachine_TClassManip(theClass);
   return theClass;
   }

   static void XRayMachine_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_XRayMachine(void *p) {
      delete ((::XRayMachine*)p);
   }
   static void deleteArray_XRayMachine(void *p) {
      delete [] ((::XRayMachine*)p);
   }
   static void destruct_XRayMachine(void *p) {
      typedef ::XRayMachine current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::XRayMachine

namespace {
  void TriggerDictionaryInitialization_libXRayMachine_Impl() {
    static const char* headers[] = {
"/Users/filippo/Developer/neuralC/XRayMachine/XRayMachine.h",
0
    };
    static const char* includePaths[] = {
"/Users/filippo/Developer/neuralC/.",
"/Users/filippo/Developer/neuralC/pcg/.",
"/Users/filippo/root/include",
"/Users/filippo/libomp/openmp/include",
"/Users/filippo/root/include",
"/Users/filippo/Developer/neuralC/build/XRayMachine/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libXRayMachine dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/Users/filippo/Developer/neuralC/XRayMachine/XRayMachine.h")))  XRayMachine;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libXRayMachine dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/filippo/Developer/neuralC/XRayMachine/XRayMachine.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"XRayMachine", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libXRayMachine",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libXRayMachine_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libXRayMachine_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libXRayMachine() {
  TriggerDictionaryInitialization_libXRayMachine_Impl();
}
