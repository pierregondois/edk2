/** @file
  Metadata Handler Library.

  Copyright (c) 2025, Arm Limited. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef METADATA_HANDLER_H_
#define METADATA_HANDLER_H_

/** Query the MetadataObjLib for metadata matching the input (Id/Token).
    If the metadata exists, return it.
    Otherwise:
    - Generate a new metadata object
    - Add it to the MetadataObjLib
    - return it

  @param[in]       Id            METADATA_ID of the entry to generate.
  @param[in]       Token         Token uniquely identifying an entry among other
                                 objects with the input METADATA_ID.
  @param[in]       Context       Optional context to use during the Metadata generation.
  @param[in, out]  Metadata      On input, can contain METADATA_ID-specific information.
                                 On output and if success, contains the generated
                                 Metadata object.
  @param[in]       MetadataSize  Size of the input Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
typedef EFI_STATUS (*METADATA_GENERATOR) (
  IN      METADATA_ID      Id,
  IN      CM_OBJECT_TOKEN  Token,
  IN      VOID             *Context,
  IN OUT  VOID             *Metadata,
  IN      UINT32           MetadataSize
  );

/** Validate the Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
typedef EFI_STATUS (*METADATA_VALIDATOR) (
  VOID
  );

/** Metadata Handlers.
 */
typedef struct MetadataHandlers {
  METADATA_GENERATOR    Generate;
  METADATA_VALIDATOR    Validate;
} METADATA_HANDLERS;

/** Query the MetadataObjLib for metadata matching the input (Id/Token).
    If the metadata exists, return it.
    Otherwise:
    - Generate a new metadata object
    - Add it to the MetadataObjLib
    - return it

  @param[in]       Id            METADATA_ID of the entry to generate.
  @param[in]       Token         Token uniquely identifying an entry among other
                                 objects with the input METADATA_ID.
  @param[in]       Context       Optional context to use during the Metadata generation.
  @param[in, out]  Metadata      On input, can contain METADATA_ID-specific information.
                                 On output and if success, contains the generated
                                 Metadata object.
  @param[in]       MetadataSize  Size of the input Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
EFI_STATUS
EFIAPI
MetadataGenerateUid (
  IN      METADATA_ID      Id,
  IN      CM_OBJECT_TOKEN  Token,
  IN      VOID             *Context,
  IN OUT  VOID             *Metadata,
  IN      UINT32           MetadataSize
  );

/** Validate the Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
EFI_STATUS
EFIAPI
MetadataValidateUid (
  VOID
  );

/** Query the MetadataObjLib for metadata matching the input (Id/Token).
    If the metadata exists, return it.
    Otherwise:
    - Generate a new metadata object
    - Add it to the MetadataObjLib
    - return it

  @param[in]       Id            METADATA_ID of the entry to generate.
  @param[in]       Token         Token uniquely identifying an entry among other
                                 objects with the input METADATA_ID.
  @param[in]       Context       Optional context to use during the Metadata generation.
  @param[in, out]  Metadata      On input, can contain METADATA_ID-specific information.
                                 On output and if success, contains the generated
                                 Metadata object.
  @param[in]       MetadataSize  Size of the input Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
EFI_STATUS
EFIAPI
MetadataGenerateProximityDomain (
  IN      METADATA_ID      Id,
  IN      CM_OBJECT_TOKEN  Token,
  IN      VOID             *Context,
  IN OUT  VOID             *Metadata,
  IN      UINT32           MetadataSize
  );

/** Validate the Metadata.

  @retval EFI_SUCCESS           Success.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
**/
EFI_STATUS
EFIAPI
MetadataValidateProximityDomain (
  VOID
  );

#endif // METADATA_HANDLER_H_
