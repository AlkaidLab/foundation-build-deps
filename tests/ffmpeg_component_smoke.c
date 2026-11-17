// ffmpeg-codec-api-20261117: send/receive; ffmpeg-bsf-api-20261117: filter
// iteration. ffmpeg-cbs-api-20261117: init/close; ffmpeg-sws-api-20261117:
// context and pixel format queries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libavcodec/avcodec.h"
#include "libavcodec/bsf.h"
#include "libavcodec/cbs.h"
#include "libavutil/samplefmt.h"
#include "libswscale/swscale.h"

#define CHECK(condition)                                                       \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #condition);             \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

static void audio_frame(enum AVCodecID id) {
  const AVCodec *codec = avcodec_find_encoder(id);
  CHECK(codec != NULL);
  AVCodecContext *ctx = avcodec_alloc_context3(codec);
  CHECK(ctx != NULL);
  ctx->sample_rate = 48000;
  ctx->sample_fmt = AV_SAMPLE_FMT_FLTP;
  ctx->bit_rate = 192000;
  ctx->ch_layout = (AVChannelLayout)AV_CHANNEL_LAYOUT_STEREO;
  CHECK(avcodec_open2(ctx, codec, NULL) == 0);
  AVFrame *frame = av_frame_alloc();
  AVPacket *packet = av_packet_alloc();
  CHECK(frame != NULL && packet != NULL);
  frame->nb_samples = ctx->frame_size;
  frame->format = ctx->sample_fmt;
  frame->sample_rate = ctx->sample_rate;
  CHECK(av_channel_layout_copy(&frame->ch_layout, &ctx->ch_layout) == 0);
  CHECK(av_frame_get_buffer(frame, 0) == 0);
  CHECK(av_samples_set_silence(frame->extended_data, 0, frame->nb_samples, 2,
                               ctx->sample_fmt) == 0);
  frame->pts = 0;
  CHECK(avcodec_send_frame(ctx, frame) == 0);
  CHECK(avcodec_receive_packet(ctx, packet) == 0);
  CHECK(packet->size > 0);
  unsigned checksum = 2166136261u;
  for (int i = 0; i < packet->size; ++i)
    checksum = (checksum ^ packet->data[i]) * 16777619u;
  printf("PASS audio %s bytes=%d checksum=%08x\n", codec->name, packet->size,
         checksum);
  av_packet_free(&packet);
  av_frame_free(&frame);
  avcodec_free_context(&ctx);
}

int main(void) {
  const char *names[] = {"h264_metadata", "hevc_metadata", "av1_metadata"};
  const enum AVCodecID ids[] = {AV_CODEC_ID_H264, AV_CODEC_ID_HEVC,
                                AV_CODEC_ID_AV1};
  for (unsigned i = 0; i < 3; ++i) {
    CHECK(av_bsf_get_by_name(names[i]) != NULL);
    CodedBitstreamContext *ctx = NULL;
    CHECK(CBS_FUNC(init)(&ctx, ids[i], NULL) == 0);
    CBS_FUNC(close)(&ctx);
  }
  void *state = NULL;
  unsigned filters = 0;
  while (av_bsf_iterate(&state))
    ++filters;
  if (EXPECT_SCOPED_BSFS)
    CHECK(filters == 3);
  CHECK(avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO) != NULL);
  CHECK(avcodec_find_encoder(AV_CODEC_ID_H263P) != NULL);
  CHECK(sws_isSupportedOutput(AV_PIX_FMT_P010LE));
  SwsContext *scale =
      sws_getContext(32, 32, AV_PIX_FMT_BGRA, 16, 16, AV_PIX_FMT_YUV420P,
                     SWS_LANCZOS, NULL, NULL, NULL);
  CHECK(scale != NULL);
  sws_freeContext(scale);
  printf("PASS component registry: 3 CBS codecs, %u filters, MPEG2/H263 "
         "encoders, swscale and P010\n",
         filters);
  audio_frame(AV_CODEC_ID_AC3);
  audio_frame(AV_CODEC_ID_EAC3);
  return 0;
}
