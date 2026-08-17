#!/usr/bin/env python3
"""Self-check for prompt expansion. Run: .venv/bin/python test_generate_image.py"""

from generate_image import PROMPT_MARKERS, SYSTEM_PROMPTS, expand_prompt

# markers must not be glued to their neighbours (the bug that produced
# "8k resolutionprofessional portrait photography" in earlier outputs)
out = expand_prompt("a woman{realism}{portrait}")
assert "woman Shot" in out, out
for name in ("realism", "portrait"):
    for word in PROMPT_MARKERS[name].split():
        assert word in out, (name, word)
assert ".Shot" not in out and ".A portrait" not in out, out
assert "  " not in out, out

# no marker -> unchanged, and unknown markers are left alone
assert expand_prompt("a woman") == "a woman"
assert expand_prompt("a woman {nope}") == "a woman {nope}"

# system prompt presets resolve by name, free-form strings pass through
assert SYSTEM_PROMPTS["aesthetics"].startswith("You are an assistant")
assert SYSTEM_PROMPTS.get("be nice", "be nice") == "be nice"

print("ok")
