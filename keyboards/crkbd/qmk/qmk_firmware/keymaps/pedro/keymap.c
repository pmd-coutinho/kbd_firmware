// ============================================================================
// Corne v4.1 Standard — urob ZMK → QMK port (QWERTY)
// ============================================================================
// Ported from: https://github.com/urob/zmk-config
// See README.md for full feature comparison.
// ============================================================================

#include QMK_KEYBOARD_H

enum layers { _DEF, _NAV, _FN, _NUM, _SYS };

enum custom_keycodes {
    NAV_LEFT = SAFE_RANGE, NAV_RIGHT, NAV_UP, NAV_DOWN,
    NAV_BSPC, NAV_DEL, ALT_TAB, QEXCL,
};

// Home row mods (GASC)
#define HM_A  LGUI_T(KC_A)
#define HM_S  LALT_T(KC_S)
#define HM_D  LSFT_T(KC_D)
#define HM_F  LCTL_T(KC_F)
#define HM_J  RCTL_T(KC_J)
#define HM_K  RSFT_T(KC_K)
#define HM_L  RALT_T(KC_L)
#define HM_SC RGUI_T(KC_SCLN)

// Thumbs
#define LT_SPC LT(_NAV, KC_SPC)
#define LT_ENT LT(_FN, KC_ENT)
#define LT_NUM MO(_NUM)

// Tap dance IDs
enum {
    TD_SFT_CW,  // Single tap = sticky shift, double tap = caps word
};
#define TD_SHFT TD(TD_SFT_CW)

// Shortcuts
#define CK_CUT  LCTL(KC_X)
#define CK_COPY LCTL(KC_INS)
#define CK_PAST LSFT(KC_INS)
#define DSK_PRV LCTL(LGUI(KC_LEFT))
#define DSK_NXT LCTL(LGUI(KC_RGHT))

// F-key HRMs (urob puts HRMs on Fn layer too)
#define HF_F11 LGUI_T(KC_F11)
#define HF_F4  LALT_T(KC_F4)
#define HF_F5  LSFT_T(KC_F5)
#define HF_F6  LCTL_T(KC_F6)

// Num HRMs
#define HN_0   LGUI_T(KC_0)
#define HN_4   LALT_T(KC_4)
#define HN_5   LSFT_T(KC_5)
#define HN_6   LCTL_T(KC_6)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Base: QWERTY (symbols on combos, mod-morphs on , . /)
    [_DEF] = LAYOUT_split_3x6_3_ex2(
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_MUTE, KC_BTN3,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
        XXXXXXX, HM_A,    HM_S,    HM_D,    HM_F,    KC_G,      KC_BSLS, KC_GRV,     KC_H,    HM_J,    HM_K,    HM_L,    HM_SC,   KC_QUOT,
        XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                             KC_N,    KC_M,    KC_COMM, KC_DOT,  QEXCL,   XXXXXXX,
                                             KC_ESC,  LT_SPC,  LT_ENT,    LT_NUM,  TD_SHFT, KC_DEL
    ),

    // Nav: arrows (tap→hold = Home/End/doc-start/doc-end/word-bspc/word-del)
    [_NAV] = LAYOUT_split_3x6_3_ex2(
        _______, LALT(KC_F4), _______, S(KC_TAB), ALT_TAB, _______,  XXXXXXX, XXXXXXX,    KC_PGUP,  NAV_BSPC, NAV_UP,   NAV_DEL,  XXXXXXX, XXXXXXX,
        _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______,  XXXXXXX, XXXXXXX,  KC_PGDN, NAV_LEFT, NAV_DOWN, NAV_RIGHT, KC_ENT, XXXXXXX,
        _______, _______,  _______,  _______,  _______,  _______,                          KC_INS,  KC_TAB,   _______,  _______,  _______, _______,
                                               _______,  _______,  _______,    _______,  KC_CANCEL, _______
    ),

    // Fn: F-keys (left, urob layout) + media (right)
    [_FN] = LAYOUT_split_3x6_3_ex2(
        _______, KC_F12,  KC_F7,   KC_F8,   KC_F9,   _______,   XXXXXXX, XXXXXXX,    _______,  KC_MPRV, KC_VOLU, KC_MNXT, _______, _______,
        _______, HF_F11,  HF_F4,   HF_F5,   HF_F6,   _______,   XXXXXXX, XXXXXXX,    _______,  DSK_PRV, KC_VOLD, DSK_NXT, _______, _______,
        _______, KC_F10,  KC_F1,   KC_F2,   KC_F3,   _______,                          _______,  _______,  _______,  _______,  _______, _______,
                                             _______,  _______,  _______,    KC_MUTE,  KC_MPLY,  _______
    ),

    // Num: numpad (left, urob layout)
    [_NUM] = LAYOUT_split_3x6_3_ex2(
        _______, _______,  KC_7,    KC_8,    KC_9,    _______,   XXXXXXX, XXXXXXX,    _______,  _______,  _______,  _______,  _______, _______,
        _______, HN_0,     HN_4,    HN_5,    HN_6,    _______,   XXXXXXX, XXXXXXX,    _______,  _______,  _______,  _______,  _______, _______,
        _______, _______,  KC_1,    KC_2,    KC_3,    _______,                          _______,  _______,  _______,  _______,  _______, _______,
                                             _______,  _______,  _______,    _______,  _______,  _______
    ),

    // Sys: boot/reset (tri-layer FN+NUM)
    [_SYS] = LAYOUT_split_3x6_3_ex2(
        _______, _______,  _______,  _______,  _______,  _______,  XXXXXXX, XXXXXXX,   _______,  _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,  _______,  _______,  QK_BOOT,  XXXXXXX, XXXXXXX,   QK_BOOT,  _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,  _______,  _______,  QK_RBT,                        QK_RBT,   _______,  _______,  _______,  _______, _______,
                                               _______,  _______,  _______,    _______,  _______,  _______
    ),
};

// Tri-layer: FN + NUM = SYS
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _FN, _NUM, _SYS);
}

// ---------------------------------------------------------------------------
// Tap Dance: Sticky Shift / Caps Word
// ---------------------------------------------------------------------------
// Single tap = one-shot shift (next key is shifted)
// Double tap = toggle Caps Word
// To cancel Caps Word: tap space, enter, comma, dot, or any non-alpha/num key
void td_sft_cw_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        set_oneshot_mods(MOD_LSFT);  // Sticky shift
    } else if (state->count >= 2) {
        caps_word_toggle();           // Toggle Caps Word
    }
}

void td_sft_cw_reset(tap_dance_state_t *state, void *user_data) {
    // Nothing to clean up
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sft_cw_finished, td_sft_cw_reset),
};

// ---------------------------------------------------------------------------
// Combos — urob's full set mapped to QWERTY physical positions
// ---------------------------------------------------------------------------
// Horizontal - left
const uint16_t PROGMEM c_esc[]   = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM c_tab[]   = {HM_S, HM_D, COMBO_END};
const uint16_t PROGMEM c_cut[]   = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM c_copy[]  = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM c_paste[] = {KC_C, KC_V, COMBO_END};

// Horizontal - right
const uint16_t PROGMEM c_bspc[]  = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM c_del[]   = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM c_lpar[]  = {HM_J, HM_K, COMBO_END};
const uint16_t PROGMEM c_rpar[]  = {HM_K, HM_L, COMBO_END};
const uint16_t PROGMEM c_lbkt[]  = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM c_rbkt[]  = {KC_COMM, KC_DOT, COMBO_END};

// Vertical - left top+mid
const uint16_t PROGMEM c_at[]    = {KC_W, HM_S, COMBO_END};
const uint16_t PROGMEM c_hash[]  = {KC_E, HM_D, COMBO_END};
const uint16_t PROGMEM c_dllr[]  = {KC_R, HM_F, COMBO_END};
const uint16_t PROGMEM c_prcnt[] = {KC_T, KC_G, COMBO_END};

// Vertical - left mid+bot
const uint16_t PROGMEM c_grave[] = {HM_S, KC_X, COMBO_END};
const uint16_t PROGMEM c_bslh[]  = {HM_D, KC_C, COMBO_END};
const uint16_t PROGMEM c_equal[] = {HM_F, KC_V, COMBO_END};
const uint16_t PROGMEM c_tilde[] = {KC_G, KC_B, COMBO_END};

// Vertical - right top+mid
const uint16_t PROGMEM c_caret[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM c_plus[]  = {KC_U, HM_J, COMBO_END};
const uint16_t PROGMEM c_star[]  = {KC_I, HM_K, COMBO_END};
const uint16_t PROGMEM c_amps[]  = {KC_O, HM_L, COMBO_END};

// Vertical - right mid+bot
const uint16_t PROGMEM c_under[] = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM c_minus[] = {HM_J, KC_M, COMBO_END};
const uint16_t PROGMEM c_fslh[]  = {HM_K, KC_COMM, COMBO_END};
const uint16_t PROGMEM c_pipe[]  = {HM_L, KC_DOT, COMBO_END};

// Caps Word
const uint16_t PROGMEM c_capsw[] = {KC_LSFT, KC_RSFT, COMBO_END};

// Combo indices (so we can filter per-combo in combo_should_trigger)
enum combo_indices {
    C_ESC, C_TAB,
    C_CUT, C_COPY, C_PASTE,
    C_BSPC, C_DEL,
    C_LPAR, C_RPAR,
    C_LBKT, C_RBKT,
    C_AT, C_HASH, C_DLLR, C_PRCNT,
    C_GRAVE, C_BSLH, C_EQUAL, C_TILDE,
    C_CARET, C_PLUS, C_STAR, C_AMPS,
    C_UNDER, C_MINUS, C_FSLH, C_PIPE,
    C_CAPSW,
    C_PAD1, C_PAD2,
};

combo_t key_combos[COMBO_COUNT] = {
    [C_ESC]   = COMBO(c_esc,   KC_ESC),    [C_TAB]   = COMBO(c_tab,   KC_TAB),
    [C_CUT]   = COMBO(c_cut,   CK_CUT),    [C_COPY]  = COMBO(c_copy,  CK_COPY),
    [C_PASTE] = COMBO(c_paste, CK_PAST),
    [C_BSPC]  = COMBO(c_bspc,  KC_BSPC),   [C_DEL]   = COMBO(c_del,   KC_DEL),
    [C_LPAR]  = COMBO(c_lpar,  KC_LPRN),   [C_RPAR]  = COMBO(c_rpar,  KC_RPRN),
    [C_LBKT]  = COMBO(c_lbkt,  KC_LBRC),   [C_RBKT]  = COMBO(c_rbkt,  KC_RBRC),
    [C_AT]    = COMBO(c_at,    KC_AT),      [C_HASH]  = COMBO(c_hash,  KC_HASH),
    [C_DLLR]  = COMBO(c_dllr,  KC_DLR),    [C_PRCNT] = COMBO(c_prcnt, KC_PERC),
    [C_GRAVE] = COMBO(c_grave, KC_GRV),     [C_BSLH]  = COMBO(c_bslh,  KC_BSLS),
    [C_EQUAL] = COMBO(c_equal, KC_EQL),     [C_TILDE] = COMBO(c_tilde, KC_TILD),
    [C_CARET] = COMBO(c_caret, KC_CIRC),    [C_PLUS]  = COMBO(c_plus,  KC_PLUS),
    [C_STAR]  = COMBO(c_star,  KC_ASTR),    [C_AMPS]  = COMBO(c_amps,  KC_AMPR),
    [C_UNDER] = COMBO(c_under, KC_UNDS),    [C_MINUS] = COMBO(c_minus, KC_MINS),
    [C_FSLH]  = COMBO(c_fslh,  KC_SLSH),    [C_PIPE]  = COMBO(c_pipe,  KC_PIPE),
    [C_CAPSW] = COMBO(c_capsw, CW_TOGG),
    [C_PAD1]  = COMBO(c_capsw, KC_NO),      [C_PAD2]  = COMBO(c_capsw, KC_NO),
};

// ---------------------------------------------------------------------------
// Per-combo idle check (urob's require-prior-idle-ms equivalent)
// ---------------------------------------------------------------------------
// Matching urob's exact combo idle values:
//   ALL horizontal combos: COMBO_IDLE_FAST = 150ms
//   ALL vertical combos:   COMBO_IDLE_SLOW = 50ms
// ---------------------------------------------------------------------------
#define COMBO_IDLE_FAST 150
#define COMBO_IDLE_SLOW 50

static uint16_t last_keypress_time = 0;

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    uint16_t idle;
    switch (combo_index) {
        // Bksp + Del — short idle, need to be responsive right after typing
        case C_BSPC:   // U+I
        case C_DEL:    // I+O
            idle = COMBO_IDLE_SLOW;
            break;

        // Other horizontal combos — COMBO_IDLE_FAST (150ms)
        case C_ESC:    // W+E
        case C_TAB:    // S+D
        case C_CUT:    // X+V
        case C_COPY:   // X+C
        case C_PASTE:  // C+V
        case C_LPAR:   // J+K
        case C_RPAR:   // K+L
        case C_LBKT:   // M+,
        case C_RBKT:   // ,+.
            idle = COMBO_IDLE_FAST;
            break;

        // Vertical combos — COMBO_IDLE_SLOW (50ms)
        case C_AT:     // W+S
        case C_HASH:   // E+D
        case C_DLLR:   // R+F
        case C_PRCNT:  // T+G
        case C_GRAVE:  // S+X
        case C_BSLH:   // D+C
        case C_EQUAL:  // F+V
        case C_TILDE:  // G+B
        case C_CARET:  // Y+H
        case C_PLUS:   // U+J
        case C_STAR:   // I+K
        case C_AMPS:   // O+L
        case C_UNDER:  // H+N
        case C_MINUS:  // J+M
        case C_FSLH:   // K+,
        case C_PIPE:   // L+.
            idle = COMBO_IDLE_SLOW;
            break;

        // Caps Word and padding — always fire
        default:
            return true;
    }
    return timer_elapsed(last_keypress_time) >= idle;
}

// ---------------------------------------------------------------------------
// Key Overrides (urob's mod-morphs)
// ---------------------------------------------------------------------------
const key_override_t ov_comma = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);  // ,→;
const key_override_t ov_dot   = ko_make_basic(MOD_MASK_SHIFT, KC_DOT,  KC_COLN);  // .→:
// ?/! morph is handled via custom QEXCL keycode in process_record_user
const key_override_t ov_bspc  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);   // bspc→del

const key_override_t *key_overrides[] = {
    &ov_comma, &ov_dot, &ov_bspc, NULL,
};

// ---------------------------------------------------------------------------
// Encoders
// ---------------------------------------------------------------------------
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_DEF] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_NAV] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D),  ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_FN]  = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),  ENCODER_CCW_CW(KC_BRID, KC_BRIU)  },
    [_NUM] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D),  ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    [_SYS] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),  ENCODER_CCW_CW(RGB_HUD, RGB_HUI)  },
};
#endif

// ---------------------------------------------------------------------------
// Caps Word
// ---------------------------------------------------------------------------
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Letters: apply shift and continue
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        // Numbers: continue without shift (for CONSTANT_123 style)
        case KC_1 ... KC_0:
            return true;

        // These continue Caps Word without shift:
        case KC_MINS:   // - (SCREAMING-KEBAB)
        case KC_UNDS:   // _ (SCREAMING_SNAKE_CASE — the main use case)
        case KC_BSPC:   // fix typos without cancelling
        case KC_DEL:
        // Mod-taps: let home row mods through so you can Ctrl+Shift+whatever
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return true;

        default:
            return false;  // Everything else cancels Caps Word
    }
}

// ---------------------------------------------------------------------------
// Nav hold-tap + Alt-Tab swapper
// ---------------------------------------------------------------------------
static uint16_t nav_timer    = 0;
static uint16_t nav_tap_kc   = 0;
static bool     nav_held     = false;
static bool     alt_tab_on   = false;

#define NAV_HOLD_MS 200

void matrix_scan_user(void) {
    if (nav_tap_kc && !nav_held && timer_elapsed(nav_timer) > NAV_HOLD_MS) {
        nav_held = true;
        unregister_code(nav_tap_kc);
    }
    if (alt_tab_on && !layer_state_is(_NAV)) {
        unregister_code(KC_LALT);
        alt_tab_on = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track last keypress time for combo idle check
    if (record->event.pressed) {
        last_keypress_time = timer_read();
    }

    // Reset nav hold on any other keypress
    if (record->event.pressed && nav_tap_kc &&
        keycode != NAV_LEFT && keycode != NAV_RIGHT &&
        keycode != NAV_UP && keycode != NAV_DOWN &&
        keycode != NAV_BSPC && keycode != NAV_DEL) {
        nav_tap_kc = 0;
    }

    switch (keycode) {
        case NAV_LEFT:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_LEFT; nav_held = false;
                register_code(KC_LEFT);
            } else {
                unregister_code(KC_LEFT);
                if (nav_held) tap_code(KC_HOME);
                nav_tap_kc = 0;
            }
            return false;

        case NAV_RIGHT:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_RIGHT; nav_held = false;
                register_code(KC_RIGHT);
            } else {
                unregister_code(KC_RIGHT);
                if (nav_held) tap_code(KC_END);
                nav_tap_kc = 0;
            }
            return false;

        case NAV_UP:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_UP; nav_held = false;
                register_code(KC_UP);
            } else {
                unregister_code(KC_UP);
                if (nav_held) { register_code(KC_LCTL); tap_code(KC_HOME); unregister_code(KC_LCTL); }
                nav_tap_kc = 0;
            }
            return false;

        case NAV_DOWN:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_DOWN; nav_held = false;
                register_code(KC_DOWN);
            } else {
                unregister_code(KC_DOWN);
                if (nav_held) { register_code(KC_LCTL); tap_code(KC_END); unregister_code(KC_LCTL); }
                nav_tap_kc = 0;
            }
            return false;

        case NAV_BSPC:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_BSPC; nav_held = false;
                register_code(KC_BSPC);
            } else {
                unregister_code(KC_BSPC);
                if (nav_held) { register_code(KC_LCTL); tap_code(KC_BSPC); unregister_code(KC_LCTL); }
                nav_tap_kc = 0;
            }
            return false;

        case NAV_DEL:
            if (record->event.pressed) {
                nav_timer = timer_read(); nav_tap_kc = KC_DEL; nav_held = false;
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
                if (nav_held) { register_code(KC_LCTL); tap_code(KC_DEL); unregister_code(KC_LCTL); }
                nav_tap_kc = 0;
            }
            return false;

        case ALT_TAB:
            if (record->event.pressed) {
                if (!alt_tab_on) { alt_tab_on = true; register_code(KC_LALT); }
                tap_code(KC_TAB);
            }
            return false;

        // QEXCL: tap = ?, shift+tap = ! (urob's qexcl morph)
        case QEXCL:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_EXLM);
                    set_mods(get_mods());
                } else {
                    tap_code16(S(KC_SLSH)); // ?
                }
            }
            return false;
    }
    return true;
}