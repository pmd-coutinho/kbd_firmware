// ============================================================================
// Corne v4.1 — urob ZMK port to QMK (QWERTY)
// ============================================================================
#pragma once

// --- Timeless home row mods (urob's core innovation) ---
#define TAPPING_TERM 280
#define QUICK_TAP_TERM 175
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD

// --- Combos ---
#define COMBO_COUNT 33
#define COMBO_TERM 30
#define COMBO_TERM_PER_COMBO
// Only fire combo if both keys pressed within COMBO_HOLD_TERM and no key
// was tapped in the prior COMBO_MUST_IDLE_MS window.
// This prevents misfires during fast rolls (urob's require-prior-idle equivalent).
#define COMBO_SHOULD_TRIGGER
#define COMBO_ONLY_FROM_LAYER 0  // _DEF

// --- Caps Word ---
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 5000

// --- One-shot mods ---
#define ONESHOT_TAP_TOGGLE 0  // Disable lock on double-tap (prevents stuck shift)
#define ONESHOT_TIMEOUT 900

// --- Custom Shift Keys ---
// Ctrl+Shift bypasses custom shift keys, restoring native Shift+,=< and Shift+.=>
#define CUSTOM_SHIFT_KEYS_NEGMODS (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))

// --- Flow Tap (urob's require-prior-idle-ms for HRMs) ---
#define FLOW_TAP_TERM 150

// --- Encoders ---
#define ENCODER_RESOLUTION 4

// --- Mouse ---
#define MK_COMBINED

// --- RGB ---
#define RGB_MATRIX_DEFAULT_VAL 30
