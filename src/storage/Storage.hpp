// Copyright (C) 2021-2022 Joel Rosdahl and other contributors
//
// See doc/AUTHORS.adoc for a complete list of contributors.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 51
// Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#pragma once

#include <core/types.hpp>
#include <storage/primary/PrimaryStorage.hpp>
#include <storage/secondary/SecondaryStorage.hpp>
#include <storage/types.hpp>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Digest;

namespace storage {

std::string get_features();

struct SecondaryStorageBackendEntry;
struct SecondaryStorageEntry;

class Storage
{
public:
  Storage(const Config& config);
  ~Storage();

  void initialize();
  void finalize();

  primary::PrimaryStorage primary;

  // Returns a path to a file containing the value.
  std::optional<std::string> get(const Digest& key, core::CacheEntryType type);

  bool put(const Digest& key,
           core::CacheEntryType type,
           const storage::EntryWriter& entry_writer);

  void remove(const Digest& key, core::CacheEntryType type);

  bool has_secondary_storage() const;
  std::string get_secondary_storage_config_for_logging() const;

private:
  const Config& m_config;
  std::vector<std::unique_ptr<SecondaryStorageEntry>> m_secondary_storages;
  std::vector<std::string> m_tmp_files;

  void add_secondary_storages();

  void
  mark_backend_as_failed(SecondaryStorageBackendEntry& backend_entry,
                         secondary::SecondaryStorage::Backend::Failure failure);

  SecondaryStorageBackendEntry*
  get_backend(SecondaryStorageEntry& entry,
              const Digest& key,
              std::string_view operation_description,
              const bool for_writing);
  std::optional<std::pair<std::string, bool>>
  get_from_secondary_storage(const Digest& key);

  void put_in_secondary_storage(const Digest& key,
                                const std::string& value,
                                bool only_if_missing);

  void remove_from_secondary_storage(const Digest& key);
};

} // namespace storage
