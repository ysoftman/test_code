# Landing Page Overrides

> **PROJECT:** Driftlog
> **Generated:** 2026-11-11 11:11:26
> **Page Type:** Landing / Marketing

> ⚠️ **IMPORTANT:** Rules in this file **override** the Master file (`design-system/MASTER.md`).
> Only deviations from the Master are documented here. For all other rules, refer to the Master.

---

## Page-Specific Rules

### Layout Overrides

- **Max Width:** 1200px (standard)
- **Layout:** Full-width sections, centered content
- **Sections:** 1. Hero, 2. Product video/mockup (center), 3. Feature breakdown per section, 4. Comparison (optional), 5. CTA

### Spacing Overrides

- No overrides — use Master spacing

### Typography Overrides

- No overrides — use Master typography

### Color Overrides

- **Strategy:** Video surround: Brand color overlay. Features: Icon color #0080FF. Text: Dark #222

### Component Overrides

- Avoid: Blank screen or '0 results'
- Avoid: Require full type and enter
- Avoid: No hover feedback on clickable elements

---

## Page-Specific Components

- No unique components for this page

---

## Recommendations

- Effects: Product animation playback, step progression animations, hover reveal effects, smooth zoom on interaction
- Search: Show 'No results' with suggestions
- Search: Show predictions as user types
- Interaction: Change cursor and add subtle visual change
- CTA Placement: Video center + CTA right/bottom

---

## Implementation Overrides (applied while building `src/`)

Recorded here per the Master + Overrides pattern; these take precedence over MASTER.md for this page.

| Item | MASTER value | Override | Reason (skill rule) |
|------|--------------|----------|---------------------|
| Primary button text | `white` on `#22C55E` (2.28:1) | `#0F172A` on `#22C55E` (7.83:1) | `color-contrast`; colors.csv lists On Accent `#0F172A` |
| Focus ring | `#1E293B` (1.22:1 on bg) | Light `#2563EB` / Dark `#60A5FA` | `focus-states`; ui-reasoning "Dark syntax theme + Blue focus" |
| Theme | Dark Mode (OLED), dark only | `prefers-color-scheme` light + dark tokens | Brief requirement; `dark-mode-pairing` |
| Light palette | n/a | bg `#F8FAFC`, surface `#FFFFFF`, fg `#0F172A`, muted-fg `#475569`, border `#E2E8F0`, accent text `#15803D` | `color-accessible-pairs` (all text >= 4.5:1) |
| Code / log surfaces | n/a | Always dark (`#0A0F1E`) in both themes | ui-reasoning "Dark syntax theme"; anti-pattern "Light mode default" |
| Feature icon color | `#0080FF` (3.80:1 on white) | Light `#0070E0` / Dark `#3B9EFF` | `color-contrast` for UI glyphs |
| Body font | Inter / Inter | Inter + Noto Sans KR (Hangul) + JetBrains Mono (code, ligatures off) | Korean copy; typography "Developer Mono" pairing; `|=` must stay literal |
| Card hover | `cursor:pointer` + lift on all cards | No hover on non-interactive cards | `cursor-pointer` only on clickable elements |
| Effects | Minimal glow | `text-shadow 0 0 10px` on hero accent (dark only), live-tail dot glow | Style key effects |
| Histogram | n/a | Stacked bars + striped ERROR texture + text annotation | chart "Anomaly Detection": shape/text not color only |
| Live tail | n/a | Pause/resume button, stops off-screen, off by default with reduced motion | chart "Real-Time Streaming" a11y fallback |
