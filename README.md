# Smiley

Converts Brainfuck into pretty smileys and vice versa. 

Why? Because we can!

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
 `>` | `:>`
 `<` | `:<`
 `+` | `:)`
 `-` | `:(`
 `.` | `:O`
 `,` | `;)`
 `[` | `:[`
 `]` | `:]`
