# Smiley

Converts Brainfuck into pretty smileys and vice versa. 

Why? That's the wrong question to ask. Why not? That's more like it.

## Usage

These instructions assume the binary is named 'smiley'.

### Brainfuck to Smiley

```
./smiley -i brainfuck.b -o smiley.s
```

### Smiley to Brainfuck

```
./smiley -i smiley.s -o brainfuck.b
```

## Mappings

Brainfuck | Smiley
 --- | --- 
 `+` | `:>`
 `-` | `:<`
 `>` | `:-)`
 `<` | `:-(`
 `[` | `:O`
 `]` | `;)`
 `.` | `<3`
 `,` | `</3`
