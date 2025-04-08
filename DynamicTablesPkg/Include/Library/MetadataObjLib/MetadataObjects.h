/** @file
  Metadata Objects.

  Copyright (c) 2025, Arm Limited. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef METADATA_OBJECTS_H_
#define METADATA_OBJECTS_H_

/** Metadata Ids

  Some general rules:
  -
  Each Id has an associated strucure.
  -
  It is possible to Add/Remove/Get the Metadata associated to
  a (Id/Token). To modify the Metadata, the object must be removed
  then added again.
  -
  A (Id/Token) pair allows to uniquely identify a Metadata structure.
  A Token might have multiple Metadata structures allocated with other Ids.
  An Id might have multiple entries with different Tokens.
*/
typedef enum MetadataId {
    MetadataUidId,
    MetadataProximityDomainId,
    MetadataMaxId,
  } METADATA_ID;
  
  /** MetadataUidId related structure.
   */
  typedef struct MetadataObjUid {
    /// Uid
    UINT32    Uid;
  
    /// _HID or _CID of the device (NULL-terminated string).
    /// This provides a mean to uniquely identify a device type.
    /// If not populated, EisaId must be set.
    CHAR8     NameId[9];
  
    /// EisaId of the device.
    /// This provides a mean to uniquely identify a device type.
    /// If not populated, NameId must be set.
    UINT32    EisaId;
  } METADATA_OBJ_UID;
  
  /** MetadataProximityDomainId related structure.
   */
  typedef struct MetadataObjProximityDomain {
    /// Proximity Domain Id
    UINT32    Id;
  } METADATA_OBJ_PROXIMITY_DOMAIN;
  
#endif // METADATA_OBJECTS_H_
