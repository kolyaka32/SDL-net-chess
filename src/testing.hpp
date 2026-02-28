/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// File for setting flags for all test for program
// Debuging modifiers
#define DEBUG true
// Logging important information
#define CHECK_CORRECTION DEBUG
// Logging all actions (including minor)
#define CHECK_ALL DEBUG
// Flag to load data from archieve (true) or straight from files (false)
#define ARCHIEVE_LOADING !(DEBUG)

// Internet testing
// Testing connection stability
#define CONNECTION_LOST_PERCENT 0
