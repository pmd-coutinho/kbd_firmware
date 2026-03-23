# Corne v4.1 — urob ZMK → QMK port (QWERTY)

A faithful port of [urob's ZMK config](https://github.com/urob/zmk-config) to QMK,
adapted for QWERTY on the Corne v4.1 Standard.

## Feature comparison

| urob ZMK feature | QMK port | Status |
|---|---|---|
| Timeless HRMs (balanced + positional + require-prior-idle) | Chordal Hold + Permissive Hold + Flow Tap (150ms) | ✅ |
| Horizontal combos (Esc, Tab, Bspc, Del, (), [], cut/copy/paste) | QMK combos, per-combo term (50ms horizontal / 30ms vertical) | ✅ |
| Vertical combos (all symbols: @#$%`\=~^+*&_-/\|) | QMK combos | ✅ |
| Per-combo require-prior-idle | combo_should_trigger (125ms horizontal / 50ms vertical) | ✅ |
| Mod-morphs (Shift+,=; Shift+.=: Shift+Bspc=Del) | getreuer/custom_shift_keys module | ✅ |
| Mod-morphs (Shift+?=! Shift+(=< Shift+)=>) | Custom keycodes (QEXCL, LPAR_LT, RPAR_GT) | ✅ |
| Nav hold-taps (arrow→Home/End, Bspc→wBspc, Del→wDel) | Custom process_record_user with double-tap-hold repeat | ✅ |
| Alt-Tab swapper | Custom process_record_user | ✅ |
| Smart-Num (auto-deactivating num layer) | Num Word: tap=toggle, hold=momentary | ✅ |
| Tri-layer (FN + NUM = SYS) | update_tri_layer_state | ✅ |
| Caps Word (both shifts) | QMK Caps Word | ✅ |
| Sticky mods on Nav layer | One-shot mods (Gui/Alt/Shift/Ctrl on home row) | ✅ |
| F-key HRMs on Fn layer | Mod-tap on F-keys | ✅ |
| Num HRMs on Num layer | Mod-tap on numbers | ✅ |
| Encoders per layer | QMK encoder map | ✅ |
| Select Word | getreuer/select_word community module on NAV bottom row | ✅ |
| Magic Shift (adaptive repeat + sticky shift) | Sticky shift only (tap dance) | ⚠️ Simplified |
| Smart-Mouse (auto-deactivating) | Skipped | ❌ |
| Leader key (Unicode/Greek/German) | Compose key (D+F combo) | ❌ Different approach |
| Shift+Space = dot+space+sticky-shift | Skipped | ❌ |

## Layers

### DEF (Base)

QWERTY with GASC home row mods. All symbols via combos. Mod-morphs on `,` `.` `?`.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │  Q  │  W  │  E  │  R  │  T  │ │  Y  │  U  │  I  │  O  │  P  │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ A   │ S   │ D   │ F   │  G  │ │  H  │ J   │ K   │ L   │ ;   │  '  │
│     │Gui  │ Alt │ Sft │ Ctl │     │ │     │ Ctl │ Sft │ Alt │ Gui │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  Z  │  X  │  C  │  V  │  B  │ │  N  │  M  │  ,  │  .  │ ?/! │     │
└─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │ Esc │Space│Enter│ │ Num │Shift│ Del │
                  │     │ NAV │ FN  │ │Word │TD/CW│     │
                  └─────┴─────┴─────┘ └─────┴─────┴─────┘
```

Thumb keys: Space=hold NAV, Enter=hold FN, Num=tap for Num Word / hold for momentary NUM.
Shift thumb: tap=sticky shift, double-tap=Caps Word, hold=regular shift.

### NAV (hold Space)

Vim-style arrows on home row with hold alternates. Select Word on bottom-right.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │AltF4│     │S-Tab│A-Tab│     │ │Bspc │PgDn │PgUp │ Del │     │     │
│     │     │     │     │     │     │ │wBspc│     │     │wDel │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ Gui │ Alt │Shift│ Ctrl│     │ │  ←  │  ↓  │  ↑  │  →  │Home │ End │
│     │ OSM │ OSM │ OSM │ OSM │     │ │Home │^End │^Home│ End │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │^Z   │^X   │^Ins │S-Ins│     │ │SelW←│SelL↓│SelL↑│SelW→│ Ins │ Tab │
└─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │▓▓▓▓▓│     │ │     │Cancl│     │
                  └─────┴─────┴─────┘ └─────┴─────┴─────┘
```

Arrow keys: tap=single press, double-tap-hold=auto-repeat, hold=alternate (shown on second line).
Bottom-right: getreuer's Select Word — select backward/forward word, select up/down line.

### FN (hold Enter)

F-keys on left (urob layout), media on right.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │ F12 │ F7  │ F8  │ F9  │     │ │     │Prev │Vol+ │Next │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ F11 │ F4  │ F5  │ F6  │     │ │     │Desk←│Vol- │Desk→│     │     │
│     │ Gui │ Alt │ Sft │ Ctl │     │ │     │G+←  │     │G+→  │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │ F10 │ F1  │ F2  │ F3  │     │ │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │▓▓▓▓▓│ │Mute │Play │     │
                  └─────┴─────┴─────┘ └─────┴─────┴─────┘
```

### NUM (tap or hold Num thumb)

Numpad on left. Tap thumb=Num Word (auto-deactivates on non-number), hold=momentary.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │  7  │  8  │  9  │     │ │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │  0  │  4  │  5  │  6  │     │ │     │     │     │     │     │     │
│     │ Gui │ Alt │ Sft │ Ctl │     │ │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │  1  │  2  │  3  │     │ │     │     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │ │▓▓▓▓▓│     │     │
                  └─────┴─────┴─────┘ └─────┴─────┴─────┘
```

Num Word allows: `0-9`, `-`, `.`, `,`, Bspc, Del, mod-taps. Everything else cancels and passes through.

### SYS (tri-layer FN + NUM)

Boot and reset on both halves.

```
┌─────┬─────┬─────┬─────┬─────┬─────┐ ┌─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │ │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │Boot │ │Boot │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │Reset│ │Reset│     │     │     │     │     │
└─────┴─────┴─────┼─────┼─────┼─────┤ ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │     │     │     │ │     │     │     │
                  └─────┴─────┴─────┘ └─────┴─────┴─────┘
```

## Combo map (QWERTY positions)

Horizontal combos use a 50ms combo term; vertical combos use 30ms.

```
Horizontal combos:
  W+E = Esc       U+I = Bspc
  S+D = Tab       I+O = Del
  D+F = Compose   J+K = (  [Shift = <]
  X+C = Copy      K+L = )  [Shift = >]
  C+V = Paste     M+, = [
  X+V = Cut       ,+. = ]

Vertical combos (top+mid):
  W+S = @    Y+H = ^
  E+D = #    U+J = +
  R+F = $    I+K = *
  T+G = %    O+L = &

Vertical combos (mid+bot):
  S+X = `    H+N = _
  D+C = \    J+M = -
  F+V = =    K+, = /
  G+B = ~    L+. = |
```

## Key behaviors

| Feature | Behavior |
|---|---|
| **Flow Tap** | During fast typing (<150ms between keys), HRM keys always tap — no accidental mod activations |
| **Num Word** | Tap num thumb → type numbers freely → auto-exits when you press a non-number key |
| **Select Word** | NAV bottom-right: SELWBAK/SELLINE/SELLUP/SELWORD for word and line selection |
| **Nav hold-taps** | Tap=arrow, hold=alternate (Home/End/wBspc/wDel), double-tap-hold=auto-repeat |
| **Custom Shift Keys** | Shift+`,`=`;`  Shift+`.`=`:`  Shift+Bspc=Del (via getreuer module) |
| **Custom mod-morphs** | Shift+`?`=`!`  Shift+`(`=`<`  Shift+`)`=`>` (via custom keycodes) |
| **Caps Word** | Both shifts or double-tap shift thumb. Allows letters, numbers, `-`, `_`, Bspc |
| **Sticky shift** | Single tap shift thumb = one-shot shift for next key |

## Build

```bash
# From the repo root:
kb=crkbd make qmk-init
kb=crkbd kr=rev4_1/standard km=pedro make qmk-compile

# Flash: hold BOOT + plug USB, copy .uf2 to RPI-RP2 drive. Both halves.
```

## Dependencies

- QMK firmware ≥ 0.32.4 (for Flow Tap and community modules)
- [getreuer/qmk-modules](https://github.com/getreuer/qmk-modules) — submodule at `src/qmk-modules/getreuer`, copied into QMK modules dir by `make qmk-init`

## Tuning

| Parameter | File | Default | Purpose |
|---|---|---|---|
| `TAPPING_TERM` | config.h | 280ms | HRM hold threshold |
| `QUICK_TAP_TERM` | config.h | 175ms | Quick tap window for HRMs |
| `FLOW_TAP_TERM` | config.h | 150ms | Fast typing threshold — keys within this window always tap |
| `COMBO_TERM` | config.h | 30ms | Vertical combo window |
| `COMBO_TERM_PER_COMBO` | keymap.c | 50ms | Horizontal combo window (via `get_combo_term()`) |
| `COMBO_IDLE_FAST` | keymap.c | 125ms | Horizontal combo idle requirement |
| `COMBO_IDLE_SLOW` | keymap.c | 50ms | Vertical combo idle requirement |
| `NAV_HOLD_MS` | keymap.c | 200ms | Nav key hold threshold for alternate action |
| `NAV_DTAP_MS` | keymap.c | 250ms | Nav double-tap window for auto-repeat |
| `ONESHOT_TIMEOUT` | config.h | 900ms | Sticky shift/mod timeout |
| `CAPS_WORD_IDLE_TIMEOUT` | config.h | 5000ms | Caps Word auto-cancel after idle |
