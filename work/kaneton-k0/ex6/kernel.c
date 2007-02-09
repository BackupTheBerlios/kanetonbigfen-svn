/*
** kernel.c for  in /home/fensoft
**
** Made by fenet_v
** Login <fenet_v@epita.fr>
**
** Started on  Sun Jan 28 12:25:20 2007 fensoft
** Last update Sun Jan 28 13:30:00 2007 fensoft
*/

char a;
char b = 42;

main()
{
  int num;
  char ch;

  char *text_video = (char*)0xB8000;
  char attrib = 0x07;
  char *str="Kernel Loaded";

  while(*str!=0)
  {
    *text_video = *str;
    *text_video++;
    *text_video = attrib;
    *text_video++;
    *str++;
  }
  return 0;
}
