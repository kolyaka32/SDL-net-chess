/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../logger.hpp"


// Check, if need to preload data
#if (PRELOAD_DATA)
// Load needed loader, depend on testing
#if (ARCHIEVE_LOADING)
#include "archieveLoader.hpp"
#define DataLoader ArchieveLoader
#else
#include "straightLoader.hpp"
#define DataLoader StraightLoader
#endif  // (ARCHIEVE_LOADING)
// Setting global dataloader
extern const DataLoader dataLoader;
#endif  // (PRELOAD_DATA)
