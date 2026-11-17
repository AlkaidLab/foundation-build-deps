# Component selection checks

This is a standalone Debug test project for a minimal FFmpeg software fixture.
Configure FFmpeg from the pinned source with avcodec, avutil, swscale and
`ac3,eac3,mpeg2video,h263p` encoders, using either the original all-BSF selection
or `h264_metadata,hevc_metadata,av1_metadata` only. Keep every other configure
option and compiler identical between the two builds.

Configure this directory with `FFMPEG_SOURCE_DIR` and `FFMPEG_BUILD_DIR` pointing
to that source and build. Set `EXPECT_SCOPED_BSFS=OFF` for the original selection.
`FFMPEG_CBS_LIBRARY` can point to the separately built CBS archive to exercise the
same symbol selection as its consumer. Build and run `ctest --output-on-failure`.
No assertions disappear when NDEBUG is defined.

The check opens H.264, HEVC and AV1 CBS contexts, verifies the BSF registry, probes
MPEG2/H263 encoders and swscale/P010 support, and encodes one silent AC3 and EAC3
frame. Both selections produced the same 768-byte packet checksums (FNV-1a):
AC3 `4bc628ad`, EAC3 `c4d50200`. The registry shrank from 50 filters to 3.
This does not verify HDR bitstreams, hardware encoders, encoding latency or quality.

The archive data in `docs/performance/ffmpeg-archive-size-20261117.json` is a Linux
software fixture, not Windows executable or installer savings. Two trials each:
25,763,562 to 19,536,862 raw bytes, 10,746,521 to 8,006,670 raw-DEFLATE bytes.
The elapsed values include reading, compression and hashing, not a full build.
The host binary baseline summary does not attribute static archives or objects;
24,801,817 text-section bytes have no source-line attribution. A link map is still
required to rank linked archives and objects, including assembly and read-only data.

The regular minimal CMake build initially failed to compile CBS because the copied
submodule git pointer was invalid and its existing patches were not applied.
Applying the repository's two existing CBS patches to the build copy allowed the
all-target build to complete. The unmodified copy/patch automation still needs
validation; this change does not repair it or claim it was a previously known failure.

NVENC, QSV, native AMF, the software video encoders, the existing hardware contexts,
and all OS-specific encoder options are retained. Their native Windows, macOS,
Linux-device and HDR runs are unverified here. No runtime wrapper or media algorithm
is added, so these measurements do not establish throughput or wrapper overhead.
