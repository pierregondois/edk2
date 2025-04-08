/** @file
  Metadata Object Library.

  Copyright (c) 2025, Arm Limited. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef METADATA_OBJ_LIB_H_
#define METADATA_OBJ_LIB_H_

#include "MetadataObjects.h"

/* Handle to an internal Metadata structure. */
typedef VOID *METADATA_HANDLE;

/** Attach some Metadata to a (Id/Token) pair.

  @param[in]  Id            METADATA_ID of the entry to allocate.
  @param[in]  Token         Token uniquely identifying an entry among other
                            objects with the input METADATA_ID.
  @param[in]  Metadata      Metadata to associate to the (Id/Token) pair.
                            The data is copied.
  @param[in]  MetadataSize  Size of the input Metadata.

  @retval EFI_SUCCESS     Success.
  @retval EFI_ALREADY_STARTED   (Id/Token) pair is already present.
  @retval EFI_INVALID_PARAMETER   Invalid parameter.
  @retval EFI_NOT_FOUND   Not found.
**/
EFI_STATUS
EFIAPI
MetadataAdd (
  IN  METADATA_ID      Id,
  IN  CM_OBJECT_TOKEN  Token,
  IN  VOID             *Metadata,
  IN  UINT32           MetadataSize
  );

/** Remove a (Id/Token) pair and its associated Metadata.

  @param[in]  Id            METADATA_ID of the entry to remove.
  @param[in]  Token         Token uniquely identifying an entry among other
                            objects with the input METADATA_ID.

  @retval EFI_SUCCESS     Success.
  @retval EFI_INVALID_PARAMETER   Invalid parameter.
  @retval EFI_NOT_FOUND   Not found.
**/
EFI_STATUS
EFIAPI
MetadataRemove (
  IN  METADATA_ID      Id,
  IN  CM_OBJECT_TOKEN  Token
  );

/** Get the Metadata associated to an (Id/Token).

  @param[in]  Id            METADATA_ID of the entry to get.
  @param[in]  Token         Token uniquely identifying an entry among other
                            objects with the input METADATA_ID.
  @param[out] Metadata      If success, contains the Metadata associated to the
                            input (Id/Token).
  @param[in]  MetadataSize  Size of the input Metadata.

  @retval EFI_SUCCESS     Success.
  @retval EFI_INVALID_PARAMETER   Invalid parameter.
  @retval EFI_NOT_FOUND   Not found.
**/
EFI_STATUS
EFIAPI
MetadataGet (
  IN   METADATA_ID      Id,
  IN   CM_OBJECT_TOKEN  Token,
  OUT  VOID             *Metadata,
  IN   UINT32           MetadataSize
  );

/** Iterate over the existing Metadata with the same Id.

  @param[in]  Id            METADATA_ID to iterate over.
  @param[in]  PrevHandle    On entry: Handle to the Metadata structure previously
                            iterated over.
                            On exit: Handle to the Metadata structure currently
                            iterated over.
  @param[out] Metadata      Metadata of the current Handle.
  @param[in]  MetadataSize  Size of the input Metadata.

  @return METADATA_HANDLE   The handle.
**/
METADATA_HANDLE
EFIAPI
MetadataIterate (
  IN  METADATA_ID      Id,
  IN  METADATA_HANDLE  PrevHandle,
  OUT VOID             *Metadata,
  IN  UINT32           MetadataSize
  );

#endif // METADATA_OBJ_LIB_H_
