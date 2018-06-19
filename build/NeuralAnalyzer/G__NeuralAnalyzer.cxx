// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__NeuralAnalyzer

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
#include "/Users/filippo/Developer/neuralC/NeuralAnalyzer/NeuralAnalyzer.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *NeuralAnalyzer_Dictionary();
   static void NeuralAnalyzer_TClassManip(TClass*);
   static void *new_NeuralAnalyzer(void *p = 0);
   static void *newArray_NeuralAnalyzer(Long_t size, void *p);
   static void delete_NeuralAnalyzer(void *p);
   static void deleteArray_NeuralAnalyzer(void *p);
   static void destruct_NeuralAnalyzer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NeuralAnalyzer*)
   {
      ::NeuralAnalyzer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::NeuralAnalyzer));
      static ::ROOT::TGenericClassInfo 
         instance("NeuralAnalyzer", "NeuralAnalyzer/NeuralAnalyzer.h", 22,
                  typeid(::NeuralAnalyzer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &NeuralAnalyzer_Dictionary, isa_proxy, 0,
                  sizeof(::NeuralAnalyzer) );
      instance.SetNew(&new_NeuralAnalyzer);
      instance.SetNewArray(&newArray_NeuralAnalyzer);
      instance.SetDelete(&delete_NeuralAnalyzer);
      instance.SetDeleteArray(&deleteArray_NeuralAnalyzer);
      instance.SetDestructor(&destruct_NeuralAnalyzer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NeuralAnalyzer*)
   {
      return GenerateInitInstanceLocal((::NeuralAnalyzer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::NeuralAnalyzer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *NeuralAnalyzer_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::NeuralAnalyzer*)0x0)->GetClass();
      NeuralAnalyzer_TClassManip(theClass);
   return theClass;
   }

   static void NeuralAnalyzer_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_NeuralAnalyzer(void *p) {
      return  p ? new(p) ::NeuralAnalyzer : new ::NeuralAnalyzer;
   }
   static void *newArray_NeuralAnalyzer(Long_t nElements, void *p) {
      return p ? new(p) ::NeuralAnalyzer[nElements] : new ::NeuralAnalyzer[nElements];
   }
   // Wrapper around operator delete
   static void delete_NeuralAnalyzer(void *p) {
      delete ((::NeuralAnalyzer*)p);
   }
   static void deleteArray_NeuralAnalyzer(void *p) {
      delete [] ((::NeuralAnalyzer*)p);
   }
   static void destruct_NeuralAnalyzer(void *p) {
      typedef ::NeuralAnalyzer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::NeuralAnalyzer

namespace {
  void TriggerDictionaryInitialization_libNeuralAnalyzer_Impl() {
    static const char* headers[] = {
"/Users/filippo/Developer/neuralC/NeuralAnalyzer/NeuralAnalyzer.h",
0
    };
    static const char* includePaths[] = {
"/Users/filippo/Developer/neuralC/.",
"/Users/filippo/Developer/neuralC/pcg/.",
"/Users/filippo/root/include",
"/Users/filippo/libomp/openmp/include",
"/Users/filippo/root/include",
"/Users/filippo/Developer/neuralC/build/NeuralAnalyzer/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libNeuralAnalyzer dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/Users/filippo/Developer/neuralC/NeuralAnalyzer/NeuralAnalyzer.h")))  NeuralAnalyzer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libNeuralAnalyzer dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/Users/filippo/Developer/neuralC/NeuralAnalyzer/NeuralAnalyzer.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"NeuralAnalyzer", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libNeuralAnalyzer",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libNeuralAnalyzer_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libNeuralAnalyzer_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libNeuralAnalyzer() {
  TriggerDictionaryInitialization_libNeuralAnalyzer_Impl();
}
