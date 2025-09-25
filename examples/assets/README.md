# Example Assets

The C++ showcase example generates its own textures and audio data at runtime. It does, however, need a TrueType font file so text widgets can render correctly.

Place a `.ttf` font inside `examples/assets/fonts/` (for example `Roboto-Regular.ttf`). The example will automatically use that font if it is present. When no font is found in this folder, the program tries a few common system fonts and finally aborts with an explanatory error message.
