# Corne v4.1 — urob ZMK → QMK port (QWERTY)

A faithful port of [urob's ZMK config](https://github.com/urob/zmk-config) to QMK,
adapted for QWERTY on the Corne v4.1 Standard.

## Feature comparison

| urob ZMK feature | QMK port | Status |
|---|---|---|
| Timeless HRMs (balanced + positional + require-prior-idle) | Chordal Hold + Permissive Hold + Quick Tap | ✅ |
| Horizontal combos (Esc, Tab, Bspc, Del, (), [], cut/copy/paste) | QMK combos | ✅ |
| Vertical combos (all symbols: @#$%`\=~^+*&_-/\|) | QMK combos | ✅ |
| Mod-morphs (Shift+,=; Shift+.=: Shift+/=! Shift+Bspc=Del) | Key overrides | ✅ |
| Nav hold-taps (arrow→Home/End, ↑→doc-start, ↓→doc-end, Bspc→word-del) | Custom process_record_user | ✅ |
| Alt-Tab swapper | Custom process_record_user | ✅ |
| Tri-layer (FN + NUM = SYS) | update_tri_layer_state | ✅ |
| Caps Word (both shifts) | QMK Caps Word | ✅ |
| Sticky mods on Nav/Fn layers | One-shot mods | ✅ |
| F-key HRMs on Fn layer | Mod-tap on F-keys | ✅ |
| Num HRMs on Num layer | Mod-tap on numbers | ✅ |
| Encoders per layer | QMK encoder map | ✅ |
| Magic Shift (adaptive repeat + sticky shift) | Sticky shift only | ⚠️ Simplified |
| Smart-Num (auto-deactivating) | Regular MO() hold | ⚠️ Simplified |
| Smart-Mouse (auto-deactivating) | Skipped | ❌ |
| Leader key (Unicode/Greek/German) | Use Compose key | ❌ Different approach |
| Shift+Space = dot+space+sticky-shift | Skipped | ❌ |

## Layers

```
DEF (Base): QWERTY + GASC home row mods. All symbols on combos.
NAV: Hold left Space. Arrows with hold=Home/End, sticky mods, Alt-Tab.
FN:  Hold left Enter. F-keys (urob layout: F12/F7-F9/F11/F4-F6/F10/F1-F3) + media.
NUM: Hold right outer thumb. Numpad on left hand (7-8-9/4-5-6/1-2-3/0).
SYS: Tri-layer FN+NUM. Boot, reset.
```

## Combo map (QWERTY positions)

```
Horizontal combos:
  W+E = Esc       U+I = Bspc
  S+D = Tab       I+O = Del
  X+C = Copy      J+K = (
  C+V = Paste     K+L = )
  X+V = Cut       M+, = [
                   ,+. = ]

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

## Build

```bash
# Copy keymap files
mkdir -p ~/qmk_firmware/keyboards/crkbd/keymaps/pedro
cp keymap.c config.h rules.mk ~/qmk_firmware/keyboards/crkbd/keymaps/pedro/

# Compile
qmk compile -kb crkbd/rev4_1/standard -km pedro

# Flash: hold BOOT + plug USB, copy .uf2 to RPI-RP2 drive. Both halves.
```

## Tuning

- **HRM misfires on same-hand rolls?** Chordal Hold should prevent this. If not, increase `TAPPING_TERM`.
- **HRM too slow to activate?** Decrease `TAPPING_TERM` (try 250).
- **Combo misfires during fast typing?** Increase `COMBO_TERM` (try 35-40).
- **Nav hold-tap threshold?** Adjust `NAV_HOLD_MS` in keymap.c (default 200ms).
- **Sticky shift timeout?** Adjust `ONESHOT_TIMEOUT` in config.h (default 900ms).
