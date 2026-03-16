#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define DualArmLearning_DLLIMPORT __declspec(dllimport)
#  define DualArmLearning_DLLEXPORT __declspec(dllexport)
#  define DualArmLearning_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define DualArmLearning_DLLIMPORT __attribute__((visibility("default")))
#    define DualArmLearning_DLLEXPORT __attribute__((visibility("default")))
#    define DualArmLearning_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define DualArmLearning_DLLIMPORT
#    define DualArmLearning_DLLEXPORT
#    define DualArmLearning_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef DualArmLearning_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define DualArmLearning_DLLAPI
#  define DualArmLearning_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef DualArmLearning_EXPORTS
#    define DualArmLearning_DLLAPI DualArmLearning_DLLEXPORT
#  else
#    define DualArmLearning_DLLAPI DualArmLearning_DLLIMPORT
#  endif // DualArmLearning_EXPORTS
#  define DualArmLearning_LOCAL DualArmLearning_DLLLOCAL
#endif // DualArmLearning_STATIC