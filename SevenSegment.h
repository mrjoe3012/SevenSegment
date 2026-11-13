/*
 * SevenSegment.h
 *
 * Author: Joseph Agrane
 * Copyright (c) 2026 Joseph Agrane
 *
 * Licensed under the MIT License.
 * See LICENSE file in the project root for details.
 */
#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

enum SevenSegment {
  SS_ZERO = 0,
  SS_ONE,
  SS_TWO,
  SS_THREE,
  SS_FOUR,
  SS_FIVE,
  SS_SIX,
  SS_SEVEN,
  SS_EIGHT,
  SS_NINE,
  SS_A,
  SS_B,
  SS_C,
  SS_D,
  SS_E,
  SS_F,
  SS_H,
  SS_L,
  SS_P,
  SS_U,
  SS_COUNT
};

#define SEVEN_SEGMENT_BYTE(a, ap, b, bp, c, cp, d, dp, e, ep, f, fp, g, gp) \
  (((g) << (gp)) | \
   ((f) << (fp)) | \
   ((e) << (ep)) | \
   ((d) << (dp)) | \
   ((c) << (cp)) | \
   ((b) << (bp)) | \
   ((a) << (ap)))

#define SEVEN_SEGMENT_LUT(ap, bp, cp, dp, ep, fp, gp) \
  { \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 1, dp, 1, ep, 1, fp, 0, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 1, bp, 1, cp, 0, dp, 0, ep, 0, fp, 0, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 0, cp, 1, dp, 1, ep, 0, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 1, dp, 0, ep, 0, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 1, bp, 1, cp, 0, dp, 0, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 0, bp, 1, cp, 1, dp, 0, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 0, bp, 1, cp, 1, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 0, dp, 0, ep, 0, fp, 0, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 1, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 1, dp, 0, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 1, cp, 0, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 0, bp, 1, cp, 1, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 0, bp, 0, cp, 1, dp, 1, ep, 1, fp, 0, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 1, bp, 1, cp, 1, dp, 1, ep, 0, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 0, bp, 0, cp, 1, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 0, bp, 0, cp, 0, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 1, bp, 1, cp, 0, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 0, bp, 0, cp, 1, dp, 1, ep, 1, fp, 0, gp), \
    SEVEN_SEGMENT_BYTE(1, ap, 1, bp, 0, cp, 0, dp, 1, ep, 1, fp, 1, gp), \
    SEVEN_SEGMENT_BYTE(0, ap, 1, bp, 1, cp, 1, dp, 1, ep, 1, fp, 0, gp), \
  }

#endif  // SEVEN_SEGMENT_H_
