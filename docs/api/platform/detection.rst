.. default-domain:: cpp
.. highlight:: cpp
.. namespace:: sdl
.. _gum-platform-detection:

CPU and Platform Detection
============================

SDL provides a way to get CPU and platform information in a cross platform way that is immediately useful.

This file can be included through::

    #include <gum/platform/name.hpp>
    #include <gum/platform/cpu.hpp>

The following functions have been remapped:

.. function:: std::string platform()

    Returns a string of the current platform. Calls :sdl:`GetPlatform` internally.
    If the platform is not found, then "Unknown" is returned. The current supported platform strings are:

    - Windows
    - Mac OS X
    - Linux
    - iOS
    - Android

.. function:: bool has_3dnow() noexcept
              bool has_avx() noexcept
              bool has_altivec() noexcept
              bool has_mmx() noexcept
              bool has_rdtsc() noexcept
              bool has_sse() noexcept
              bool has_sse2() noexcept
              bool has_sse3() noexcept
              bool has_sse41() noexcept
              bool has_sse42() noexcept

    Calls the appropriate SDL function that checks for these CPU specific intrinsics.
.. function:: int system_ram() noexcept

    Returns the amount of RAM the system has in MiB. Calls :sdl:`GetSystemRAM` internally.
.. function:: int logical_cpu_cores() noexcept

    Returns the number of logical CPU cores. This means that systems with a hyperthreading model will
    have a higher result than the physical cores. Calls :sdl:`GetCPUCount` internally.
.. function:: int cpu_cache_line_size() noexcept

    Returns the number of KiB of the system's L1 cache size. Calls :sdl:`GetCPUCacheLineSize` internally.
