#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SAIDA if(key[KEY_ESC]) exit_program = TRUE;

volatile int exit_program = FALSE;

void fechar_programa()
{
    exit_program = TRUE;
}
END_OF_FUNCTION(fechar_programa)


int main()
{
    ///ALLEGRO INPUT
    allegro_init();
    install_timer();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1300, 650, 0, 0);
    set_window_title("Batalha Naval 1.0");
    LOCK_VARIABLE(exit_program);
    LOCK_FUNCTION(fechar_programa);
    set_close_button_callback(fechar_programa);
    ///END ALLEGRO

    ///FONT
    FONT* arial_48 = load_font("arial_48.pcx", NULL, NULL);
    FONT* stencil_22 = load_font("stencil_22.pcx", NULL, NULL);
    FONT* gothic_18 = load_font("gothic_18.pcx", NULL, NULL);
    ///END FONT

    ///BITMAPS
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* mar = load_bitmap("sprites/mar.bmp", NULL);
    BITMAP* explosion = load_bitmap("sprites/explosion.bmp", NULL);
    ///END BITMAP

    ///VARIABLE
    int r = 255, g = 255, b = 255;
    int bomba = -2, mares = -2;
    int pos_bomba[24], pos_mar[486];
    int i, h, j = 0, ver = 0, hor = 0;
    int finded = 0, tiros = 0;
    int qnt_ships = 0;
    int **m1;
    ///END VARIABLE

    ///DYNAMIC ALLOCATION AND MATRIX RESET
    m1 = (int **) malloc(15*sizeof(int *));
	for(i = 0; i < 15; i++)
	{
		m1[i] = (int *) malloc(15*sizeof(int));
	}

	for(i = 0; i < 15; i++)
	{
		for(h = 0; h < 15; h++)
		{
			m1[i][h] = 0;
		}
	}
    ///END MALLOC

    ///RANDOM SHIPS
    srand(time(NULL));

	for(i = 0; i < 12; i++)
	{
		m1[rand() % 15][rand() % 15] = 1;
	}
	///END SHIPS

	///NUMBER OF SHIPS
	for(i = 0; i < 15; i++)
	{
		for(h = 0; h < 15; h++)
		{
			if(m1[i][h] == 1) qnt_ships++;
		}
	}
	///END OF COUNT


   while(!exit_program)
   {
        ///SCREEN
        textout_centre_ex(screen, arial_48, "Batalha Naval", SCREEN_W/2, SCREEN_H/2-100, makecol(r, g, b), -1);
        textout_centre_ex(screen, font, "Pressione ENTER para continuar", SCREEN_W/2, SCREEN_H/2+15, makecol(r, g, b), -1);
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
        ///END SCREEN

        ///COLOR CHANGE
        if(r < 255)
        {
            r++;
        }
        else
        {
            if(g < 255)
            {
                g++;
            }
            else
            {
                if(b < 255)
                {
                    b++;
                }
                else
                {
                    r = 0;
                    b = 125;
                    g = 0;
                }
            }
        }
        ///END COLOR

    SAIDA

    if(key[KEY_ENTER] || key[KEY_ENTER_PAD])
    {
         clear(screen);
         while(!exit_program)
         {
            ///SCREEN
            textout_centre_ex(screen, arial_48, "Batalha Naval", SCREEN_W/2, SCREEN_H/2-100, makecol(r, g, b), -1);
            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
            textout_centre_ex(screen, stencil_22, "1. JOGAR (vs NPC)", SCREEN_W/2, SCREEN_H/2, makecol(255, 255, 255), -1);
            textout_centre_ex(screen, stencil_22, "2. INSTRUCOES", SCREEN_W/2, SCREEN_H/2+50, makecol(255, 255, 255), -1);
            ///END SCREEN

            ///COLOR CHANGE
            if(r < 255)
             {
                 r++;
             }
             else
             {
                 if(g < 255)
                 {
                     g++;
                 }
                 else
                 {
                     if(b < 255)
                     {
                         b++;
                     }
                     else
                     {
                         r = 0;
                         b = 125;
                         g = 0;
                     }
                 }
             }
             ///END COLOR

            SAIDA

            ///PLAY
            if(key[KEY_1] || key[KEY_1_PAD])
            {
                clear(screen);
                while(!exit_program)
                {
                    ///SCREEN
                    textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
                    textout_centre_ex(buffer, arial_48, "Batalha Naval", SCREEN_W/2-30, 30, makecol(0, 0, 255), -1);
                    textprintf_centre_ex(buffer, stencil_22, 200, 150, makecol(255, 255, 255), -1, "Use as setas para");
                    textprintf_centre_ex(buffer, stencil_22, 200, 180, makecol(255, 255, 255), -1, "mirar e espaco");
                    textprintf_centre_ex(buffer, stencil_22, 200, 210, makecol(255, 255, 255), -1, "para atirar");
                    ///END SCREEN


                    for(i = 0; i <= 15; i++)
                    {
                        line(buffer, 400, j+150, 850, j+150, makecol(0,0,255));
                        line(buffer, j+400, 150, j+400, 600, makecol(0,0,255));
                        j += 30;
                    }
                    j = 0;

                    char tecla = readkey() >> 8;

                    if(tecla == KEY_RIGHT) hor += 30;
                    if(hor > 420) hor = 0;
                    if(tecla == KEY_LEFT) hor -= 30;
                    if(hor < 0) hor = 420;
                    if(tecla == KEY_DOWN) ver += 30;
                    if(ver > 420) ver = 0;
                    if(tecla == KEY_UP) ver -= 30;
                    if(ver < 0) ver = 420;

                    line(buffer, hor+400, ver+150, hor+430, ver+180, makecol(255,0,0));
                    line(buffer, hor+430, ver+150, hor+400, ver+180, makecol(255,0,0));

                    if(tecla == KEY_SPACE)
                    {
                        if(m1[hor/30][ver/30] == 1)
                        {
                            bomba += 2;
                            pos_bomba[bomba] = hor;
                            pos_bomba[bomba+1] = ver;
                            finded++;
                        }
                        else
                        {
                            mares += 2;
                            pos_mar[mares] = hor;
                            pos_mar[mares+1] = ver;
                            tiros++;
                        }
                    }

                    textprintf_ex(buffer, gothic_18, 880, 150, makecol(255, 255, 255), -1, "Submarinos encontrados: %d/%d", finded, qnt_ships);
                    textprintf_ex(buffer, gothic_18, 880, 180, makecol(255, 255, 255), -1, "Tentativas: %d/150", tiros);

                    for(i = 0; i <= bomba; i+=2)
                    {
                        draw_sprite_ex(buffer, explosion, 400+pos_bomba[i], 150+pos_bomba[i+1], DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
                    }

                    for(i = 0; i <= mares; i+=2)
                    {
                        draw_sprite_ex(buffer, mar, 400+pos_mar[i], 150+pos_mar[i+1], DRAW_SPRITE_NORMAL, DRAW_SPRITE_NO_FLIP);
                    }

                    draw_sprite(screen, buffer, 0, 0);
                    clear(buffer);

                    if(tiros == 150)
                    {
                        clear(screen);

                        while(!exit_program)
                        {
                            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
                            textout_centre_ex(screen, arial_48, "VOCE PERDEU!!", SCREEN_W/2, SCREEN_H/2-100, makecol(r, g, b), -1);
                            textprintf_centre_ex(screen, gothic_18, SCREEN_W/2, SCREEN_H/2 + 100, makecol(255, 255, 255), -1, "Submarinos encontrados: %d/%d", finded, qnt_ships);

                            ///COLOR CHANGE
                            if(r < 255)
                             {
                                 r++;
                             }
                             else
                             {
                                 if(g < 255)
                                 {
                                     g++;
                                 }
                                 else
                                 {
                                     if(b < 255)
                                     {
                                         b++;
                                     }
                                     else
                                     {
                                         r = 0;
                                         b = 125;
                                         g = 0;
                                     }
                                 }
                             }
                             ///END COLOR

                             SAIDA
                        }
                    }

                    if(finded == qnt_ships)
                    {
                        clear(screen);

                        while(!exit_program)
                        {
                            textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
                            textout_centre_ex(screen, arial_48, "VOCE VENCEU!!", SCREEN_W/2, SCREEN_H/2-100, makecol(r, g, b), -1);
                            textprintf_centre_ex(screen, gothic_18, SCREEN_W/2, SCREEN_H/2 + 100, makecol(255, 255, 255), -1, "Tentativas: %d", tiros);

                            ///COLOR CHANGE
                            if(r < 255)
                             {
                                 r++;
                             }
                             else
                             {
                                 if(g < 255)
                                 {
                                     g++;
                                 }
                                 else
                                 {
                                     if(b < 255)
                                     {
                                         b++;
                                     }
                                     else
                                     {
                                         r = 0;
                                         b = 125;
                                         g = 0;
                                     }
                                 }
                             }
                             ///END COLOR

                             SAIDA
                        }
                    }

                    SAIDA
                }
            }
            ///END PLAY

            ///INSTRUCTIONS
            if(key[KEY_2] || key[KEY_2_PAD])
            {
                clear(screen);
                while(!key[KEY_B] && !exit_program)
                {
                    textprintf_ex(screen, font, 10, 10, makecol(255, 255, 255), -1, "ESC para sair");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 50, makecol(255, 255, 255), -1, "INSTRUCOES");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 200, makecol(255, 255, 255), -1, "Existe uma quantidade aleatoria de submarinos, variando");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 230, makecol(255, 255, 255), -1, "de 0 a 12. Descubra todos eles para vencer.");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 260, makecol(255, 255, 255), -1, "(cuidado para nao atirar duas vezes no mesmo");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 290, makecol(255, 255, 255), -1, "lugar. tente vencer com a menor quantidade de");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 320, makecol(255, 255, 255), -1, "tiros possivel)");
                    textprintf_centre_ex(screen, stencil_22, SCREEN_W/2, 370, makecol(255, 255, 255), -1, "boa sorte!!");
                    textprintf_centre_ex(screen, font, SCREEN_W/2, 600, makecol(255, 255, 255), -1, "B para voltar");

                    SAIDA
                }
                clear(screen);
            }
            ///END INSTRUCTIONS
         }
    }

   }

   ///END OF MAIN
   destroy_font(arial_48);
   destroy_font(stencil_22);
   destroy_font(gothic_18);
   destroy_bitmap(buffer);
   destroy_bitmap(mar);
   destroy_bitmap(explosion);
   for(i = 0; i < 15; i++)
	{
		free(m1[i]);
	}
	free(m1);
   ///END OF MAIN

   return 0;
}
END_OF_MAIN()
