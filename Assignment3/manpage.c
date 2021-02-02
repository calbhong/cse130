
/*********************************************************************
 *
 * Copyright (C) 2020-2021 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 *
 ***********************************************************************/

#include "manpage.h"

/*
 * See manpage.h for details.
 *
 * As supplied, shows random single messages.
 */
void manpage() 
{
  int pid = getParagraphId(); // pid = 'Paragraph Id"
  showParagraph();
}
