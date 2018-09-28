//
//  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//

#include <AsmMacroIoLibV8.h>

ASM_FUNC(_ModuleEntryPoint)
  // Do early platform specific actions
  bl    ASM_PFX(ArmPlatformPeiBootAction)

  // Get ID of this CPU in Multicore system
  bl    ASM_PFX(ArmReadMpidr)
  // Keep a copy of the MpId register value
  mov   x10, x0

_SetSVCMode:
// Check if we can install the stack at the top of the System Memory or if we need
// to install the stacks at the bottom of the Firmware Device (case the FD is located
// at the top of the DRAM)
_SystemMemoryEndInit:
  ldr   x1, mSystemMemoryEnd //= PcdSystemMemoryBase + PcdSystemMemorySize -1 = 0x8000 0000 + 0x7F00 0000 - 1 = 0xFEFF FFFF

_SetupStackPosition:
  // r1 = SystemMemoryTop

  // Calculate Top of the Firmware Device
  MOV64 (x2, FixedPcdGet64(PcdFdBaseAddress)) //=  0x8800 0000
  MOV32 (x3, FixedPcdGet32(PcdFdSize) - 1) // = 0x0400 0000 - 1 = 0x03FF FFFF
  sub   x3, x3, #1							// = 0x03FF FFFE             ???????????????????????????????????????
  add   x3, x3, x2      // x3 = FdTop = PcdFdBaseAddress + PcdFdSize = 0x8BFF FFFE

  // UEFI Memory Size (stacks are allocated in this region)
  MOV32 (x4, FixedPcdGet32(PcdSystemMemoryUefiRegionSize)) //= 0x0400 0000

  //
  // Reserve the memory for the UEFI region (contain stacks on its top)
  //

  // Calculate how much space there is between the top of the Firmware and the Top of the System Memory
  subs  x0, x1, x3   // x0 = SystemMemoryTop - FdTop = 0xFEFF FFFF - 0x8BFF FFFE = 0x7300 0001
  b.mi  _SetupStack  // Jump if negative (FdTop > SystemMemoryTop). Case when the PrePi is in XIP memory outside of the DRAM
  cmp   x0, x4        	// We have x0 > x4 (==)0x7300 0001 > 0x0400 0000
  b.ge  _SetupStack		// We jump

  // Case the top of stacks is the FdBaseAddress
  mov   x1, x2

_SetupStack:
  // x1 contains the top of the stack (and the UEFI Memory)

  // Because the 'push' instruction is equivalent to 'stmdb' (decrement before), we need to increment
  // one to the top of the stack. We check if incrementing one does not overflow (case of DRAM at the
  // top of the memory space)
  adds  x11, x1, #1      // x11 = SystemMemoryTop + 1 = 0xFF00 0000
  b.cs  _SetupOverflowStack // We don t jump

_SetupAlignedStack:
  mov   x1, x11			 // x1 = SystemMemoryTop = 0xFF00 0000
  b     _GetBaseUefiMemory

_SetupOverflowStack:
  // Case memory at the top of the address space. Ensure the top of the stack is EFI_PAGE_SIZE
  // aligned (64KB)
  and   x1, x1, ~EFI_PAGE_MASK 			// should not use this

_GetBaseUefiMemory:
  // Calculate the Base of the UEFI Memory
  sub   x11, x1, x4   // x11 = SystemMemoryTop - PcdSystemMemoryUefiRegionSize = 0xFF00 0000 - 0x0400 0000 = 0xFB00 0000

_GetStackBase:
  // r1 = The top of the Mpcore Stacks
  // Stack for the primary core = PrimaryCoreStack
  MOV32 (x2, FixedPcdGet32(PcdCPUCorePrimaryStackSize))  // = 0x4000
  sub   x12, x1, x2         // x12 = SystemMemoryTop - PcdFdBaseAddress = 0xFF00 0000 - 0x4000 = 0xFEFF C000

  // Stack for the secondary core = Number of Cores - 1
  MOV32 (x1, (FixedPcdGet32(PcdCoreCount) - 1) * FixedPcdGet32(PcdCPUCoreSecondaryStackSize)) // = 0 * 0 = 0
  sub   x12, x12, x1   // x12 = x12 - 0  = 0xFEFF C000

  // x12 = The base of the MpCore Stacks (primary stack & secondary stacks)
  mov   x0, x12     // x0 = 0xFEFF C000
  mov   x1, x10 	// x1 = MpId register value
  //ArmPlatformStackSet(StackBase, MpId, PrimaryStackSize, SecondaryStackSize)
  MOV32 (x2, FixedPcdGet32(PcdCPUCorePrimaryStackSize))			// x2 = 0x4000
  MOV32 (x3, FixedPcdGet32(PcdCPUCoreSecondaryStackSize))		// x3 = 0x0
  bl    ASM_PFX(ArmPlatformStackSet)

  // Is it the Primary Core ?
  mov   x0, x10				// x0 = x10 = MpId register value
  bl    ASM_PFX(ArmPlatformIsPrimaryCore)
  cmp   x0, #1
  bne   _PrepareArguments

_PrepareArguments:
  mov   x0, x10
  mov   x1, x11
  mov   x2, x12

  // Move sec startup address into a data register
  // Ensure we're jumping to FV version of the code (not boot remapped alias)
  ldr   x4, =ASM_PFX(CEntryPoint)

  // Jump to PrePiCore C code
  //    x0 = MpId
  //    x1 = UefiMemoryBase
  //    x2 = StacksBase
  blr   x4

_NeverReturn:
  b _NeverReturn
