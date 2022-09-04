/**
 * \file IfxCpu_Cstart.h
 * \brief This file contains the Core startup sequence.
 *
 *
 * \version iLLD_1_0_1_12_0_1
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \defgroup IfxLld_Cpu_CStart Core Startup Functions
 * \ingroup IfxLld_Cpu
 *
 * \defgroup IfxLld_Cpu_CStart_StartupSequence Startup Sequence
 * \ingroup IfxLld_Cpu_CStart
 *
 * \defgroup IfxLld_Cpu_CStart_ConfigEnableCache How to enable cache during startup?
 * \ingroup IfxLld_Cpu_CStart
 *
 * \defgroup IfxLld_Cpu_CStart_ConfigEnableCores How to enable CPUs during startup?
 * \ingroup IfxLld_Cpu_CStart
 */
#ifndef IFXCPU_CSTART_H_
#define IFXCPU_CSTART_H_

/******************************************************************************/
/*                           Includes                                         */
/******************************************************************************/
#include "Ifx_Cfg.h"
#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER
#include "Cpu/Std/Ifx_Types.h"
#include "Tricore/Compilers/Compilers.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"

/******************************************************************************/
/*                           Macros                                           */
/******************************************************************************/

/** \brief Configuration for pre initialization hook function.
 *
 */
#ifndef IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK
#   define IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK(cpu) /**< Hook function is empty if not configured*/
#endif
/******************************************************************************/
/*                         Exported prototypes                                */
/******************************************************************************/
void _Core1_start(void);
void _Core2_start(void);

/*Documentation */

/** \addtogroup IfxLld_Cpu_CStart_StartupSequence
 * \{
 *
 * The startup driver is responsible for initializing the basic features of microcontroller
 * to bring it up to the user functions. In framework these functions are called as "CoreX_main".
 *
 * In TC27X controllers, CPU0 is master controller which is booted from reset.
 * IfxCpu_CStart driver provides following functionalities and they are listed in the order of
 * their execution.
 *
 * \section IfxLld_Cpu_CStart_StartupSequence Core Startup Sequence
 * 1) Execute pre-initialization hook, which is user configurable. \ref IfxLld_Cpu_CStart_ConfigStartupPreInitHook\n
 * 2) Setup user stack pointer for the CPU core\n
 * 3) Set program/data cache bypass to configuration defined settings. Refer \ref IfxLld_Cpu_CStart_ConfigEnableCache.\n
 * 4) Set base address for trap vector and interrupt vector for the CPU core\n
 * 5) Set interrupt stack pointer\n
 * 6) Initialize the base pointers for the small data area registers for CPU core\n
 * 7) Initialize the CSA for CPU core\n
 * 8) Do the C initialization to initialize the global variables etc.\n
 * 9) Initialize the clock system to configuration defined settings. \ref Ifx_Scu_Ccu_ConfigClock\n
 * 10) Start remaining cores if they configuration setting request them to be enabled. \ref IfxLld_Cpu_CStart_ConfigEnableCores\n
 * 11) Call user function "CoreX_main"\n
 *
 * \note All the above functionalities are executed by "master core" in this case CPU0. Remaining cores will execute
 * only subset of the above functions, i.e. steps 8) 9) and 10) are not executed by remaining CPU core startups.
 *
 * \section IfxLld_Cpu_CStart_ConfigStartupPreInitHook Using Startup pre-initialization hook
 *
 * If the application/ demo example need some activity other than above defined functionalities, user can configure
 * the function which is called before any other initialization is executed. Example of such activity is testing the CSA and STACK.
 *
 * Following are the steps to be done to configure user defined activity which is needed before startup sequence.
 *
 * \subsection IfxLld_Cpu_CStart_ConfigStartupPreInitHookStep1 Step1: Define a hook function
 *
 * This definition shall be as user defined code (Generally in DemoApps folder).\n
 * Considerations:\n
 * 1. Format: IFX_INLINE void \<pre init function name\>(cpu)
 * \note Define such a routine with the consideration, that there shall be no function call within this.
 *
 * 2. Use the information available as parameter cpu
 *
 * Example code in a user defined file eg. Ifx_preInitHook.h, placed under folder/subfolder: 0_AppSw/Tricore/DemoApp:
 * \code
 * // file: Ifx_preInitHook.h
 * //Example function for pre initialization Hook for startup functions.
 *
 * IFX_INLINE mySysPreInitHook(uint32 cpu)
 * {
 *   switch (cpu)
 *   {
 *     case 0:
 *     {
 *       //user code for cpu0: Function calls NOT allowed.
 *       break;
 *     }
 *     case 1:
 *     {
 *       //user code for cpu1: Function calls NOT allowed.
 *       break;
 *     }
 *     case 2:
 *     {
 *       //user code for cpu2: Function calls NOT allowed.
 *       break;
 *     }
 *     case default:
 *     {
 *       break;
 *     }
 *   }
 * }
 * \endcode
 *
 * \subsection IfxLld_Cpu_CStart_ConfigStartupPreInitHookStep2 Step2: Configure the pre initialization function for startup sequence call
 * Create a file for configuring the hook. For example, Ifx_Cfg_CStart.h at ../0_Src/0_AppSw/Config/Tricore (or in DemoApp folder)
 * \note This configuration, overload the macro IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK(cpu), which is already defined in IfxCpu_CStart.h.
 * !!IMPORTANT!! Don't modify this at IfxCpu_CStart.h, because this is library file.
 *
 * \code
 * //file: Ifx_Cfg_CStart.h
 *
 * #include "Ifx_preInitHook.h" //Assuming this is the file name as in above example
 *
 * #define IFX_CFG_CPU_CSTART_PRE_C_INIT_HOOK(cpu)  mySysPreInitHook(cpu) //This is INLINE function.
 *
 * \endcode
 */

/** \} */

/** \addtogroup IfxLld_Cpu_CStart_ConfigEnableCache
 * \{
 *
 * In Tricore Cpu the cache enable/ disable are handled by the feature called cache bypass.
 * Cache is enabled if the Bypass is disabled.
 *
 * Startup sequence of each CPU execute the function to do the cache settings. \ref Ifx_Cpu_StartupSequence
 * The configuration parameters IFX_CFG_CPU_CSTART_ENABLE_TRICOREx_PCACHE and
 * IFX_CFG_CPU_CSTART_ENABLE_TRICOREx_DCACHE control this function.
 *
 * To modify the default configuration, these macros are to be defined in Ifx_Cfg.h (usually located under ../0_Src/0_AppSw/Config/Common/Ifx_Cfg.h)
 * \note This kind of definitions overload the macros, which are already defined in IfxCpu_CStart*.c.
 * !!IMPORTANT!! Don't modify these in IfxCpu_CStart*.c, because theseare library files.
 *
 * Details of configuration parameters:\n
 *
 * \paragraph IfxLld_Cpu_CStart_ConfigEnableCachePgmParamters program cache configuration parameters
 *
 * Enable/Disable program cache of Tricore CPU0 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE0_PCACHE\n
 *
 * Enable/Disable program cache of Tricore CPU1 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE1_PCACHE\n
 *
 * Enable/Disable program cache of Tricore CPU2 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE2_PCACHE\n
 *
 * Enable/Disable data cache of Tricore CPU0 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE0_DCACHE\n
 *
 * Enable/Disable data cache of Tricore CPU1 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE1_DCACHE\n
 *
 * Enable/Disable data cache of Tricore CPU2 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE2_DCACHE\n
 *
 * Following example shows, how to enable program cache of all available cores and disable data cache of all
 * the available cores.
 * \code
 * //file: Ifx_Cfg.h
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE0_PCACHE  (1)   //Program cache for Cpu0 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE0_DCACHE  (1)   //Data cache for Cpu0 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE1_PCACHE  (1)   //Program cache for Cpu1 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE1_DCACHE  (1)   //Data cache for Cpu1 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE2_PCACHE  (1)   //Program cache for Cpu2 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE2_DCACHE  (1)   //Data cache for Cpu2 is enabled
 *
 * \endcode
 *
 * To control the the caches during runtime, refer for the details of APIs: \ref Ifx_Cpu_Cache
 *
 */

/** \} */

/** \addtogroup IfxLld_Cpu_CStart_ConfigEnableCores
 * \{
 *
 * Startup sequence of CPU0 execute the function to initialize the remaining available CPUs.
 * \ref IfxLld_Cpu_CStart_StartupSequence.
 * Startup sequence enables all the available CPUs.
 *
 * The configuration parameters IFX_CFG_CPU_CSTART_ENABLE_TRICOREx control this function.
 * To modify the default configuration, these macros are to be defined. Create a file to define these macros,
 * for example, Ifx_Cfg_CStart.h at ../0_Src/0_AppSw/Config/Tricore (or in DemoApp folder).
 * \note This kind of definitions, overload the macros, which are already defined in IfxCpu_CStart.h.
 * !!IMPORTANT!! Don't modify these at IfxCpu_CStart.h, because this is library file.
 *
 * Details of configuration parameters:\n
 *
 * \paragraph IfxLld_Cpu_CStart_ConfigEnableCoresParamters CPU enable/disable configuration parameters
 *
 * Enable/Disable of Tricore CPU0 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE0\n
 *
 * Enable/Disable of Tricore CPU1 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE1\n
 *
 * Enable/Disable of Tricore CPU2 with parameter:\n
 * IFX_CFG_CPU_CSTART_ENABLE_TRICORE2\n
 *
 * Following example shows, how to enable all available cores.
 * \code
 * //file: Ifx_Cfg_CStart.h
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE0 (1)   //Cpu0 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE1 (1)   //Cpu1 is enabled
 *
 * #define IFX_CFG_CPU_CSTART_ENABLE_TRICORE2 (1)   //Cpu2 is enabled
 *
 * \endcode
 *
 */

/** \} */

#endif /*#ifndef IFX_CFG_USE_COMPILER_DEFAULT_LINKER */
#endif /* IFXCPU_CSTART_H_ */
