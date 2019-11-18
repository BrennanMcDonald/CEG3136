#ifndef _LCD_ASM_H
#define _LCD_ASM_H

// Function Prototypes to Assembly Routines - Entry points
void  instr8(char);
void  data8(char);
void  lcd_init(void);
void  clear_lcd(void);
void  type_lcd(char*);
void  set_lcd_addr(char);

#endif /* _LCD_ASM_H */
