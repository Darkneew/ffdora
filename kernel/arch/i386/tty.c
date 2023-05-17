#include  <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;


char* get_clavier(void) {
	return("&&&&&'(-&_&&)=&&azertyuiop^$&&qsdfghjklm&&&*wxcvbn,;:!&*& &&1234567890&+&&AZERTYUIOP&&&&QSDFGHJKLM%&&&WXCVBN?./&&*& &");
}

char* get_perso( int rand, int stat){
	char* perso[161][8];
	perso[0][0]="Aatrox";perso[0][1]="Male";perso[0][2]="Top";perso[0][3]="Darkin";perso[0][4]="Manaless";perso[0][5]="Melee";perso[0][6]="Runterra";perso[0][7]="2013";
	perso[1][0]="Ahri";perso[1][1]="Female";perso[1][2]="Middle";perso[1][3]="Vesani";perso[1][4]="Mana";perso[1][5]="Ranged";perso[1][6]="Ionia";perso[1][7]="2011";
	perso[2][0]="Akali";perso[2][1]="Female";perso[2][2]="Top";perso[2][3]="Human";perso[2][4]="Energy";perso[2][5]="Melee";perso[2][6]="Ionia";perso[2][7]="2010";
	perso[3][0]="Akshan";perso[3][1]="Male";perso[3][2]="Middle";perso[3][3]="Human";perso[3][4]="Mana";perso[3][5]="Ranged";perso[3][6]="Shurima";perso[3][7]="2021";
	perso[4][0]="Alistar";perso[4][1]="Male";perso[4][2]="Support";perso[4][3]="Minotaur";perso[4][4]="Mana";perso[4][5]="Melee";perso[4][6]="Runeterra";perso[4][7]="2009";
	perso[5][0]="Amumu";perso[5][1]="Male";perso[5][2]="Jungle";perso[5][3]="Yordle";perso[5][4]="Mana";perso[5][5]="Melee";perso[5][6]="Shurima";perso[5][7]="2009";
	perso[6][0]="Anivia";perso[6][1]="Female";perso[6][2]="Middle";perso[6][3]="Spirit God";perso[6][4]="Mana";perso[6][5]="Ranged";perso[6][6]="Freljord";perso[6][7]="2009";
	perso[7][0]="Annie";perso[7][1]="Female";perso[7][2]="Middle";perso[7][3]="Human";perso[7][4]="Mana";perso[7][5]="Ranged";perso[7][6]="Runeterra";perso[7][7]="2009";
	perso[8][0]="Aphelios";perso[8][1]="Male";perso[8][2]="Bottom";perso[8][3]="Humans";perso[8][4]="Mana";perso[8][5]="Ranged";perso[8][6]="Targon";perso[8][7]="2019";
	perso[9][0]="Ashe";perso[9][1]="Female";perso[9][2]="Bottom";perso[9][3]="Human";perso[9][4]="Mana";perso[9][5]="Ranged";perso[9][6]="Freljord";perso[9][7]="2009";
	perso[10][0]="Aurelion Sol";perso[10][1]="Male";perso[10][2]="Middle";perso[10][3]="Celestial";perso[10][4]="Mana";perso[10][5]="Ranged";perso[10][6]="Runeterra";perso[10][7]="2016";
	perso[11][0]="Azir";perso[11][1]="Male";perso[11][2]="Middle";perso[11][3]="God-Warrior";perso[11][4]="Mana";perso[11][5]="Ranged";perso[11][6]="Shurima";perso[11][7]="2014";
	perso[12][0]="Bard";perso[12][1]="Male";perso[12][2]="Support";perso[12][3]="Celestial";perso[12][4]="Mana";perso[12][5]="Ranged";perso[12][6]="Runeterra";perso[12][7]="2015";
	perso[13][0]="Bel'Veth";perso[13][1]="Female";perso[13][2]="";perso[13][3]="Void-Being";perso[13][4]="Manaless";perso[13][5]="Melee";perso[13][6]="Void";perso[13][7]="se':";
	perso[14][0]="Blitzcrank";perso[14][1]="Other";perso[14][2]="Support";perso[14][3]="Golem";perso[14][4]="Mana";perso[14][5]="Melee";perso[14][6]="Zaun";perso[14][7]="2009";
	perso[15][0]="Brand";perso[15][1]="Male";perso[15][2]="Support";perso[15][3]="Human";perso[15][4]="Mana";perso[15][5]="Ranged";perso[15][6]="Runeterra";perso[15][7]="2011";
	perso[16][0]="Braum";perso[16][1]="Male";perso[16][2]="Support";perso[16][3]="Human";perso[16][4]="Mana";perso[16][5]="Melee";perso[16][6]="Freljord";perso[16][7]="2014";
	perso[17][0]="Caitlyn";perso[17][1]="Female";perso[17][2]="Bottom";perso[17][3]="Human";perso[17][4]="Mana";perso[17][5]="Ranged";perso[17][6]="Piltover";perso[17][7]="2011";
	perso[18][0]="Camille";perso[18][1]="Female";perso[18][2]="Top";perso[18][3]="Human";perso[18][4]="Mana";perso[18][5]="Melee";perso[18][6]="Piltover";perso[18][7]="2016";
	perso[19][0]="Cassiopeia";perso[19][1]="Female";perso[19][2]="Middle";perso[19][3]="Human";perso[19][4]="Mana";perso[19][5]="Ranged";perso[19][6]="Noxus";perso[19][7]="2010";
	perso[20][0]="Cho'Gath";perso[20][1]="Other";perso[20][2]="";perso[20][3]="Void-Being";perso[20][4]="Mana";perso[20][5]="Melee";perso[20][6]="Void";perso[20][7]="se':";
	perso[21][0]="Corki";perso[21][1]="Male";perso[21][2]="Middle";perso[21][3]="Yordle";perso[21][4]="Mana";perso[21][5]="Ranged";perso[21][6]="Bandle City";perso[21][7]="2009";
	perso[22][0]="Darius";perso[22][1]="Male";perso[22][2]="Top";perso[22][3]="Human";perso[22][4]="Mana";perso[22][5]="Melee";perso[22][6]="Noxus";perso[22][7]="2012";
	perso[23][0]="Diana";perso[23][1]="Female";perso[23][2]="Jungle";perso[23][3]="Aspect";perso[23][4]="Mana";perso[23][5]="Melee";perso[23][6]="Targon";perso[23][7]="2012";
	perso[24][0]="Dr. Mundo";perso[24][1]="Male";perso[24][2]="Top";perso[24][3]="Human";perso[24][4]="Health";perso[24][5]="Melee";perso[24][6]="Zaun";perso[24][7]="2009";
	perso[25][0]="Draven";perso[25][1]="Male";perso[25][2]="Bottom";perso[25][3]="Human";perso[25][4]="Mana";perso[25][5]="Ranged";perso[25][6]="Noxus";perso[25][7]="2012";
	perso[26][0]="Ekko";perso[26][1]="Male";perso[26][2]="Jungle";perso[26][3]="Human";perso[26][4]="Mana";perso[26][5]="Melee";perso[26][6]="Zaun";perso[26][7]="2015";
	perso[27][0]="Elise";perso[27][1]="Female";perso[27][2]="Jungle";perso[27][3]="Human";perso[27][4]="Mana";perso[27][5]="Ranged";perso[27][6]="Shadow Isles";perso[27][7]="2012";
	perso[28][0]="Evelynn";perso[28][1]="Female";perso[28][2]="Jungle";perso[28][3]="Demon";perso[28][4]="Mana";perso[28][5]="Melee";perso[28][6]="Runeterra";perso[28][7]="2009";
	perso[29][0]="Ezreal";perso[29][1]="Male";perso[29][2]="Bottom";perso[29][3]="Human";perso[29][4]="Mana";perso[29][5]="Ranged";perso[29][6]="Piltover";perso[29][7]="2010";
	perso[30][0]="Fiddlesticks";perso[30][1]="Other";perso[30][2]="Jungle";perso[30][3]="Demon";perso[30][4]="Mana";perso[30][5]="Ranged";perso[30][6]="Runeterra";perso[30][7]="2009";
	perso[31][0]="Fiora";perso[31][1]="Female";perso[31][2]="Top";perso[31][3]="Human";perso[31][4]="Mana";perso[31][5]="Melee";perso[31][6]="Demacia";perso[31][7]="2012";
	perso[32][0]="Fizz";perso[32][1]="Male";perso[32][2]="Middle";perso[32][3]="Yordle";perso[32][4]="Mana";perso[32][5]="Melee";perso[32][6]="Bilgewater";perso[32][7]="2011";
	perso[33][0]="Galio";perso[33][1]="Male";perso[33][2]="Middle";perso[33][3]="Golem";perso[33][4]="Mana";perso[33][5]="Melee";perso[33][6]="Demacia";perso[33][7]="2010";
	perso[34][0]="Gangplank";perso[34][1]="Male";perso[34][2]="Top";perso[34][3]="Human";perso[34][4]="Mana";perso[34][5]="Melee";perso[34][6]="Bilgewater";perso[34][7]="2009";
	perso[35][0]="Garen";perso[35][1]="Male";perso[35][2]="Top";perso[35][3]="Human";perso[35][4]="Manaless";perso[35][5]="Melee";perso[35][6]="Demacia";perso[35][7]="2010";
	perso[36][0]="Gnar";perso[36][1]="Male";perso[36][2]="Top";perso[36][3]="ecies";perso[36][4]="Rage";perso[36][5]="Ranged";perso[36][6]="Freljord";perso[36][7]="2014";
	perso[37][0]="Gragas";perso[37][1]="Male";perso[37][2]="Jungle";perso[37][3]="Human";perso[37][4]="Mana";perso[37][5]="Melee";perso[37][6]="Freljord";perso[37][7]="2010";
	perso[38][0]="Graves";perso[38][1]="Male";perso[38][2]="Jungle";perso[38][3]="Human";perso[38][4]="Mana";perso[38][5]="Ranged";perso[38][6]="Bilgewater";perso[38][7]="2011";
	perso[39][0]="Gwen";perso[39][1]="Female";perso[39][2]="Top";perso[39][3]="Human";perso[39][4]="Mana";perso[39][5]="Melee";perso[39][6]="Shadow Isles";perso[39][7]="2021";
	perso[40][0]="Hecarim";perso[40][1]="Male";perso[40][2]="Jungle";perso[40][3]="Undead";perso[40][4]="Mana";perso[40][5]="Melee";perso[40][6]="Shadow Isles";perso[40][7]="2012";
	perso[41][0]="Heimerdinger";perso[41][1]="Male";perso[41][2]="Middle";perso[41][3]="Yordle";perso[41][4]="Mana";perso[41][5]="Ranged";perso[41][6]="Piltover";perso[41][7]="2009";
	perso[42][0]="Illaoi";perso[42][1]="Female";perso[42][2]="Top";perso[42][3]="Human";perso[42][4]="Mana";perso[42][5]="Melee";perso[42][6]="Bilgewater";perso[42][7]="2015";
	perso[43][0]="Irelia";perso[43][1]="Female";perso[43][2]="Top";perso[43][3]="Human";perso[43][4]="Mana";perso[43][5]="Melee";perso[43][6]="Ionia";perso[43][7]="2010";
	perso[44][0]="Ivern";perso[44][1]="Male";perso[44][2]="Jungle";perso[44][3]="Human";perso[44][4]="Mana";perso[44][5]="Ranged";perso[44][6]="Ionia";perso[44][7]="2016";
	perso[45][0]="Janna";perso[45][1]="Female";perso[45][2]="Support";perso[45][3]="Spirit God";perso[45][4]="Mana";perso[45][5]="Ranged";perso[45][6]="Zaun";perso[45][7]="2009";
	perso[46][0]="Jarvan_IV";perso[46][1]="Male";perso[46][2]="Jungle";perso[46][3]="Human";perso[46][4]="Mana";perso[46][5]="Melee";perso[46][6]="Demacia";perso[46][7]="2011";
	perso[47][0]="Jax";perso[47][1]="Male";perso[47][2]="Top";perso[47][3]="Unknown";perso[47][4]="Mana";perso[47][5]="Melee";perso[47][6]="Runeterra";perso[47][7]="2009";
	perso[48][0]="Jayce";perso[48][1]="Male";perso[48][2]="Top";perso[48][3]="pecies";perso[48][4]="Mana";perso[48][5]="Melee";perso[48][6]="Piltover";perso[48][7]="2012";
	perso[49][0]="Jhin";perso[49][1]="Male";perso[49][2]="Bottom";perso[49][3]="Human";perso[49][4]="Mana";perso[49][5]="Ranged";perso[49][6]="Ionia";perso[49][7]="2016";
	perso[50][0]="Jinx";perso[50][1]="Female";perso[50][2]="Bottom";perso[50][3]="Human";perso[50][4]="Mana";perso[50][5]="Ranged";perso[50][6]="Zaun";perso[50][7]="2013";
	perso[51][0]="Kai'Sa";perso[51][1]="Female";perso[51][2]=" [";perso[51][3]="Human";perso[51][4]="Mana";perso[51][5]="Ranged";perso[51][6]="Void";perso[51][7]="': 2";
	perso[52][0]="Kalista";perso[52][1]="Female";perso[52][2]="Bottom";perso[52][3]="Wraith";perso[52][4]="Mana";perso[52][5]="Ranged";perso[52][6]="Shadow Isles";perso[52][7]="2014";
	perso[53][0]="Karma";perso[53][1]="Female";perso[53][2]="Support";perso[53][3]="Human";perso[53][4]="Mana";perso[53][5]="Ranged";perso[53][6]="Ionia";perso[53][7]="2011";
	perso[54][0]="Karthus";perso[54][1]="Male";perso[54][2]="Jungle";perso[54][3]="Wraith";perso[54][4]="Mana";perso[54][5]="Ranged";perso[54][6]="Shadow Isles";perso[54][7]="2009";
	perso[55][0]="Kassadin";perso[55][1]="Male";perso[55][2]="Middle";perso[55][3]="Human";perso[55][4]="Mana";perso[55][5]="Melee";perso[55][6]="Void";perso[55][7]="2009";
	perso[56][0]="Katarina";perso[56][1]="Female";perso[56][2]="Middle";perso[56][3]="Human";perso[56][4]="Manaless";perso[56][5]="Melee";perso[56][6]="Noxus";perso[56][7]="2009";
	perso[57][0]="Kayle";perso[57][1]="Female";perso[57][2]="Top";perso[57][3]="Human";perso[57][4]="Mana";perso[57][5]="Melee";perso[57][6]="Demacia";perso[57][7]="2009";
	perso[58][0]="Kayn";perso[58][1]="Male";perso[58][2]="Jungle";perso[58][3]="Darkin";perso[58][4]="Mana";perso[58][5]="Melee";perso[58][6]="Ionia";perso[58][7]="2017";
	perso[59][0]="Kennen";perso[59][1]="Male";perso[59][2]="Top";perso[59][3]="Yordle";perso[59][4]="Energy";perso[59][5]="Ranged";perso[59][6]="Ionia";perso[59][7]="2010";
	perso[60][0]="Kha";perso[60][1]="Male";perso[60][2]=": [";perso[60][3]="Void-Being";perso[60][4]="Mana";perso[60][5]="Melee";perso[60][6]="Void";perso[60][7]="e': ";
	perso[61][0]="Kindred";perso[61][1]="Other";perso[61][2]="Jungle";perso[61][3]="Spirit God";perso[61][4]="Mana";perso[61][5]="Ranged";perso[61][6]="Runeterra";perso[61][7]="2015";
	perso[62][0]="Kled";perso[62][1]="Male";perso[62][2]="Top";perso[62][3]="Yordle";perso[62][4]="Courage";perso[62][5]="Melee";perso[62][6]="Noxus";perso[62][7]="2016";
	perso[63][0]="Kog";perso[63][1]="Male";perso[63][2]=": [";perso[63][3]="Void-Being";perso[63][4]="Mana";perso[63][5]="Ranged";perso[63][6]="Void";perso[63][7]="e': ";
	perso[64][0]="LeBlanc";perso[64][1]="Female";perso[64][2]="Middle";perso[64][3]="Human";perso[64][4]="Mana";perso[64][5]="Ranged";perso[64][6]="Noxus";perso[64][7]="2010";
	perso[65][0]="Lee Sin";perso[65][1]="Male";perso[65][2]="Jungle";perso[65][3]="Human";perso[65][4]="Energy";perso[65][5]="Melee";perso[65][6]="Ionia";perso[65][7]="2011";
	perso[66][0]="Leona";perso[66][1]="Female";perso[66][2]="Support";perso[66][3]="Aspect";perso[66][4]="Mana";perso[66][5]="Melee";perso[66][6]="Targon";perso[66][7]="2011";
	perso[67][0]="Lillia";perso[67][1]="Female";perso[67][2]="Jungle";perso[67][3]="Fae Fawn";perso[67][4]="Mana";perso[67][5]="Ranged";perso[67][6]="Ionia";perso[67][7]="2020";
	perso[68][0]="Lissandra";perso[68][1]="Female";perso[68][2]="Middle";perso[68][3]="Human";perso[68][4]="Mana";perso[68][5]="Ranged";perso[68][6]="Freljord";perso[68][7]="2013";
	perso[69][0]="Lucian";perso[69][1]="Male";perso[69][2]="Bottom";perso[69][3]="Human";perso[69][4]="Mana";perso[69][5]="Ranged";perso[69][6]="Demacia";perso[69][7]="2013";
	perso[70][0]="Lulu";perso[70][1]="Female";perso[70][2]="Support";perso[70][3]="Yordle";perso[70][4]="Mana";perso[70][5]="Ranged";perso[70][6]="Bandle City";perso[70][7]="2012";
	perso[71][0]="Lux";perso[71][1]="Female";perso[71][2]="Middle";perso[71][3]="Human";perso[71][4]="Mana";perso[71][5]="Ranged";perso[71][6]="Demacia";perso[71][7]="2010";
	perso[72][0]="Malphite";perso[72][1]="Male";perso[72][2]="Top";perso[72][3]="Golem";perso[72][4]="Mana";perso[72][5]="Melee";perso[72][6]="Ixtal";perso[72][7]="2009";
	perso[73][0]="Malzahar";perso[73][1]="Male";perso[73][2]="Middle";perso[73][3]="Human";perso[73][4]="Mana";perso[73][5]="Ranged";perso[73][6]="Void";perso[73][7]="2010";
	perso[74][0]="Maokai";perso[74][1]="Male";perso[74][2]="Top";perso[74][3]="Treant";perso[74][4]="Mana";perso[74][5]="Melee";perso[74][6]="Shadow Isles";perso[74][7]="2011";
	perso[75][0]="Master Yi";perso[75][1]="Male";perso[75][2]="Jungle";perso[75][3]="Human";perso[75][4]="Mana";perso[75][5]="Melee";perso[75][6]="Ionia";perso[75][7]="2009";
	perso[76][0]="Miss Fortune";perso[76][1]="Female";perso[76][2]="Bottom";perso[76][3]="Human";perso[76][4]="Mana";perso[76][5]="Ranged";perso[76][6]="Bilgewater";perso[76][7]="2010";
	perso[77][0]="Mordekaiser";perso[77][1]="Male";perso[77][2]="Top";perso[77][3]="Revenant";perso[77][4]="Shield";perso[77][5]="Melee";perso[77][6]="Noxus";perso[77][7]="2010";
	perso[78][0]="Morgana";perso[78][1]="Female";perso[78][2]="Support";perso[78][3]="Human";perso[78][4]="Mana";perso[78][5]="Ranged";perso[78][6]="Demacia";perso[78][7]="2009";
	perso[79][0]="Nami";perso[79][1]="Female";perso[79][2]="Support";perso[79][3]="Marai";perso[79][4]="Mana";perso[79][5]="Ranged";perso[79][6]="Runeterra";perso[79][7]="2012";
	perso[80][0]="Nasus";perso[80][1]="Male";perso[80][2]="Top";perso[80][3]="God-Warrior";perso[80][4]="Mana";perso[80][5]="Melee";perso[80][6]="Shurima";perso[80][7]="2009";
	perso[81][0]="Nautilus";perso[81][1]="Male";perso[81][2]="Support";perso[81][3]="Revenant";perso[81][4]="Mana";perso[81][5]="Melee";perso[81][6]="Bilgewater";perso[81][7]="2012";
	perso[82][0]="Neeko";perso[82][1]="Female";perso[82][2]="Middle";perso[82][3]="Oovi-Kat";perso[82][4]="Mana";perso[82][5]="Ranged";perso[82][6]="Ixtal";perso[82][7]="2018";
	perso[83][0]="Nidalee";perso[83][1]="Female";perso[83][2]="Jungle";perso[83][3]="Human";perso[83][4]="Mana";perso[83][5]="Ranged";perso[83][6]="Ixtal";perso[83][7]="2009";
	perso[84][0]="Nilah";perso[84][1]="Female";perso[84][2]="Bottom";perso[84][3]="Human";perso[84][4]="Mana";perso[84][5]="Melee";perso[84][6]="Kathkan";perso[84][7]="2022";
	perso[85][0]="Nocturne";perso[85][1]="Other";perso[85][2]="Jungle";perso[85][3]="Demon";perso[85][4]="Mana";perso[85][5]="Melee";perso[85][6]="Runeterra";perso[85][7]="2011";
	perso[86][0]="Nunu";perso[86][1]="Male";perso[86][2]="Jungle";perso[86][3]="Human";perso[86][4]="Mana";perso[86][5]="Melee";perso[86][6]="Freljord";perso[86][7]="2009";
	perso[87][0]="Olaf";perso[87][1]="Male";perso[87][2]="Jungle";perso[87][3]="Human";perso[87][4]="Mana";perso[87][5]="Melee";perso[87][6]="Freljord";perso[87][7]="2010";
	perso[88][0]="Orianna";perso[88][1]="Female";perso[88][2]="Middle";perso[88][3]="Golem";perso[88][4]="Mana";perso[88][5]="Ranged";perso[88][6]="Piltover";perso[88][7]="2011";
	perso[89][0]="Ornn";perso[89][1]="Male";perso[89][2]="Top";perso[89][3]="Spirit God";perso[89][4]="Mana";perso[89][5]="Melee";perso[89][6]="Freljord";perso[89][7]="2017";
	perso[90][0]="Pantheon";perso[90][1]="Male";perso[90][2]="Middle";perso[90][3]="Human";perso[90][4]="Mana";perso[90][5]="Melee";perso[90][6]="Targon";perso[90][7]="2010";
	perso[91][0]="Poppy";perso[91][1]="Female";perso[91][2]="Top";perso[91][3]="Yordle";perso[91][4]="Mana";perso[91][5]="Melee";perso[91][6]="Demacia";perso[91][7]="2010";
	perso[92][0]="Pyke";perso[92][1]="Male";perso[92][2]="Support";perso[92][3]="Revenant";perso[92][4]="Mana";perso[92][5]="Melee";perso[92][6]="Bilgewater";perso[92][7]="2018";
	perso[93][0]="Qiyana";perso[93][1]="Female";perso[93][2]="Middle";perso[93][3]="Human";perso[93][4]="Mana";perso[93][5]="Melee";perso[93][6]="Ixtal";perso[93][7]="2019";
	perso[94][0]="Quinn";perso[94][1]="Female";perso[94][2]="Top";perso[94][3]="Human";perso[94][4]="Mana";perso[94][5]="Ranged";perso[94][6]="Demacia";perso[94][7]="2013";
	perso[95][0]="Rakan";perso[95][1]="Male";perso[95][2]="Support";perso[95][3]="Vastayan";perso[95][4]="Mana";perso[95][5]="Ranged";perso[95][6]="Ionia";perso[95][7]="2017";
	perso[96][0]="Rammus";perso[96][1]="Male";perso[96][2]="Jungle";perso[96][3]="God-Warrior";perso[96][4]="Mana";perso[96][5]="Melee";perso[96][6]="Shurima";perso[96][7]="2009";
	perso[97][0]="Rek'Sai";perso[97][1]="Female";perso[97][2]=": [";perso[97][3]="Void-Being";perso[97][4]="Rage";perso[97][5]="Melee";perso[97][6]="Void";perso[97][7]="e': ";
	perso[98][0]="Rell";perso[98][1]="Female";perso[98][2]="Support";perso[98][3]="Human";perso[98][4]="Mana";perso[98][5]="Melee";perso[98][6]="Noxus";perso[98][7]="2020";
	perso[99][0]="Renata Glasc";perso[99][1]="Female";perso[99][2]="Support";perso[99][3]="Human";perso[99][4]="Mana";perso[99][5]="Ranged";perso[99][6]="Zaun";perso[99][7]="2022";
	perso[100][0]="Renekton";perso[100][1]="Male";perso[100][2]="Top";perso[100][3]="God-Warrior";perso[100][4]="Fury";perso[100][5]="Melee";perso[100][6]="Shurima";perso[100][7]="2011";
	perso[101][0]="Rengar";perso[101][1]="Male";perso[101][2]="Jungle";perso[101][3]="Vastayan";perso[101][4]="Ferocity";perso[101][5]="Melee";perso[101][6]="Ixtal";perso[101][7]="2012";
	perso[102][0]="Riven";perso[102][1]="Female";perso[102][2]="Top";perso[102][3]="Human";perso[102][4]="Manaless";perso[102][5]="Melee";perso[102][6]="Ionia";perso[102][7]="2011";
	perso[103][0]="Rumble";perso[103][1]="Male";perso[103][2]="Top";perso[103][3]="Yordle";perso[103][4]="Heat";perso[103][5]="Melee";perso[103][6]="Bandle City";perso[103][7]="2011";
	perso[104][0]="Ryze";perso[104][1]="Male";perso[104][2]="Middle";perso[104][3]="Human";perso[104][4]="Mana";perso[104][5]="Ranged";perso[104][6]="Runeterra";perso[104][7]="2009";
	perso[105][0]="Samira";perso[105][1]="Female";perso[105][2]="Bottom";perso[105][3]="Human";perso[105][4]="Mana";perso[105][5]="Ranged";perso[105][6]="Shurima";perso[105][7]="2020";
	perso[106][0]="Sejuani";perso[106][1]="Female";perso[106][2]="Jungle";perso[106][3]="Human";perso[106][4]="Mana";perso[106][5]="Melee";perso[106][6]="Freljord";perso[106][7]="2012";
	perso[107][0]="Senna";perso[107][1]="Female";perso[107][2]="Support";perso[107][3]="Human";perso[107][4]="Mana";perso[107][5]="Ranged";perso[107][6]="Blessed Isles";perso[107][7]="2019";
	perso[108][0]="Seraphine";perso[108][1]="Female";perso[108][2]="Support";perso[108][3]="Human";perso[108][4]="Mana";perso[108][5]="Ranged";perso[108][6]="Piltover";perso[108][7]="2020";
	perso[109][0]="Sett";perso[109][1]="Male";perso[109][2]="Top";perso[109][3]="Human";perso[109][4]="Grit";perso[109][5]="Melee";perso[109][6]="Ionia";perso[109][7]="2020";
	perso[110][0]="Shaco";perso[110][1]="Male";perso[110][2]="Jungle";perso[110][3]="Spirit";perso[110][4]="Mana";perso[110][5]="Melee";perso[110][6]="Runeterra";perso[110][7]="2009";
	perso[111][0]="Shen";perso[111][1]="Male";perso[111][2]="Top";perso[111][3]="Human";perso[111][4]="Energy";perso[111][5]="Melee";perso[111][6]="Ionia";perso[111][7]="2010";
	perso[112][0]="Shyvana";perso[112][1]="Female";perso[112][2]="Jungle";perso[112][3]="Terrestrial Dragon";perso[112][4]="Fury";perso[112][5]="Melee";perso[112][6]="Demacia";perso[112][7]="2011";
	perso[113][0]="Singed";perso[113][1]="Male";perso[113][2]="Top";perso[113][3]="Human";perso[113][4]="Mana";perso[113][5]="Melee";perso[113][6]="Zaun";perso[113][7]="2009";
	perso[114][0]="Sion";perso[114][1]="Male";perso[114][2]="Top";perso[114][3]="Revenant";perso[114][4]="Mana";perso[114][5]="Melee";perso[114][6]="Noxus";perso[114][7]="2009";
	perso[115][0]="Sivir";perso[115][1]="Female";perso[115][2]="Bottom";perso[115][3]="Human";perso[115][4]="Mana";perso[115][5]="Ranged";perso[115][6]="Shurima";perso[115][7]="2009";
	perso[116][0]="Skarner";perso[116][1]="Male";perso[116][2]="Jungle";perso[116][3]="Brackern";perso[116][4]="Mana";perso[116][5]="Melee";perso[116][6]="Shurima";perso[116][7]="2011";
	perso[117][0]="Sona";perso[117][1]="Female";perso[117][2]="Support";perso[117][3]="Human";perso[117][4]="Mana";perso[117][5]="Ranged";perso[117][6]="Demacia";perso[117][7]="2010";
	perso[118][0]="Soraka";perso[118][1]="Female";perso[118][2]="Support";perso[118][3]="Celestial";perso[118][4]="Mana";perso[118][5]="Ranged";perso[118][6]="Targon";perso[118][7]="2009";
	perso[119][0]="Swain";perso[119][1]="Male";perso[119][2]="Top";perso[119][3]="Human";perso[119][4]="Mana";perso[119][5]="Ranged";perso[119][6]="Noxus";perso[119][7]="2010";
	perso[120][0]="Sylas";perso[120][1]="Male";perso[120][2]="Middle";perso[120][3]="Human";perso[120][4]="Mana";perso[120][5]="Melee";perso[120][6]="Demacia";perso[120][7]="2019";
	perso[121][0]="Syndra";perso[121][1]="Female";perso[121][2]="Middle";perso[121][3]="Human";perso[121][4]="Mana";perso[121][5]="Ranged";perso[121][6]="Ionia";perso[121][7]="2012";
	perso[122][0]="Tahm Kench";perso[122][1]="Male";perso[122][2]="Top";perso[122][3]="Demon";perso[122][4]="Mana";perso[122][5]="Melee";perso[122][6]="Bilgewater";perso[122][7]="2015";
	perso[123][0]="Taliyah";perso[123][1]="Female";perso[123][2]="Jungle";perso[123][3]="Human";perso[123][4]="Mana";perso[123][5]="Ranged";perso[123][6]="Shurima";perso[123][7]="2016";
	perso[124][0]="Talon";perso[124][1]="Male";perso[124][2]="Middle";perso[124][3]="Human";perso[124][4]="Mana";perso[124][5]="Melee";perso[124][6]="Noxus";perso[124][7]="2011";
	perso[125][0]="Taric";perso[125][1]="Male";perso[125][2]="Support";perso[125][3]="Aspect";perso[125][4]="Mana";perso[125][5]="Melee";perso[125][6]="Targon";perso[125][7]="2009";
	perso[126][0]="Teemo";perso[126][1]="Male";perso[126][2]="Top";perso[126][3]="Yordle";perso[126][4]="Mana";perso[126][5]="Ranged";perso[126][6]="Bandle City";perso[126][7]="2009";
	perso[127][0]="Thresh";perso[127][1]="Male";perso[127][2]="Support";perso[127][3]="Wraith";perso[127][4]="Mana";perso[127][5]="Ranged";perso[127][6]="Shadow Isles";perso[127][7]="2013";
	perso[128][0]="Tristana";perso[128][1]="Female";perso[128][2]="Bottom";perso[128][3]="Yordle";perso[128][4]="Mana";perso[128][5]="Ranged";perso[128][6]="Bandle City";perso[128][7]="2009";
	perso[129][0]="Trundle";perso[129][1]="Male";perso[129][2]="Jungle";perso[129][3]="Troll";perso[129][4]="Mana";perso[129][5]="Melee";perso[129][6]="Freljord";perso[129][7]="2010";
	perso[130][0]="Tryndamere";perso[130][1]="Male";perso[130][2]="Top";perso[130][3]="Human";perso[130][4]="Fury";perso[130][5]="Melee";perso[130][6]="Freljord";perso[130][7]="2009";
	perso[131][0]="Twisted Fate";perso[131][1]="Male";perso[131][2]="Middle";perso[131][3]="Human";perso[131][4]="Mana";perso[131][5]="Ranged";perso[131][6]="Bilgewater";perso[131][7]="2009";
	perso[132][0]="Twitch";perso[132][1]="Male";perso[132][2]="Bottom";perso[132][3]="Plague Rat";perso[132][4]="Mana";perso[132][5]="Ranged";perso[132][6]="Zaun";perso[132][7]="2009";
	perso[133][0]="Udyr";perso[133][1]="Male";perso[133][2]="Jungle";perso[133][3]="Human";perso[133][4]="Mana";perso[133][5]="Melee";perso[133][6]="Freljord";perso[133][7]="2009";
	perso[134][0]="Urgot";perso[134][1]="Male";perso[134][2]="Top";perso[134][3]="Human";perso[134][4]="Mana";perso[134][5]="Ranged";perso[134][6]="Noxus";perso[134][7]="2010";
	perso[135][0]="Varus";perso[135][1]="Male";perso[135][2]="Bottom";perso[135][3]="Darkin";perso[135][4]="Mana";perso[135][5]="Ranged";perso[135][6]="Ionia";perso[135][7]="2012";
	perso[136][0]="Vayne";perso[136][1]="Female";perso[136][2]="Top";perso[136][3]="Human";perso[136][4]="Mana";perso[136][5]="Ranged";perso[136][6]="Demacia";perso[136][7]="2011";
	perso[137][0]="Veigar";perso[137][1]="Male";perso[137][2]="Middle";perso[137][3]="Yordle";perso[137][4]="Mana";perso[137][5]="Ranged";perso[137][6]="Runeterra";perso[137][7]="2009";
	perso[138][0]="Vel";perso[138][1]="Male";perso[138][2]=": [";perso[138][3]="Void-Being";perso[138][4]="Mana";perso[138][5]="Ranged";perso[138][6]="Void";perso[138][7]="e': ";
	perso[139][0]="Vex";perso[139][1]="Female";perso[139][2]="Middle";perso[139][3]="Yordle";perso[139][4]="Mana";perso[139][5]="Ranged";perso[139][6]="Shadow Isles";perso[139][7]="2021";
	perso[140][0]="Vi";perso[140][1]="Female";perso[140][2]="Jungle";perso[140][3]="Human";perso[140][4]="Mana";perso[140][5]="Melee";perso[140][6]="Piltover";perso[140][7]="2012";
	perso[141][0]="Viego";perso[141][1]="Male";perso[141][2]="Jungle";perso[141][3]="Wraith";perso[141][4]="Manaless";perso[141][5]="Melee";perso[141][6]="Shadow Isles";perso[141][7]="2021";
	perso[142][0]="Viktor";perso[142][1]="Male";perso[142][2]="Middle";perso[142][3]="Human";perso[142][4]="Mana";perso[142][5]="Ranged";perso[142][6]="Zaun";perso[142][7]="2011";
	perso[143][0]="Vladimir";perso[143][1]="Male";perso[143][2]="Top";perso[143][3]="Human";perso[143][4]="Bloodthirst";perso[143][5]="Ranged";perso[143][6]="Noxus";perso[143][7]="2010";
	perso[144][0]="Volibear";perso[144][1]="Male";perso[144][2]="Top";perso[144][3]="Spirit God";perso[144][4]="Mana";perso[144][5]="Melee";perso[144][6]="Freljord";perso[144][7]="2011";
	perso[145][0]="Warwick";perso[145][1]="Male";perso[145][2]="Jungle";perso[145][3]="Human";perso[145][4]="Mana";perso[145][5]="Melee";perso[145][6]="Zaun";perso[145][7]="2009";
	perso[146][0]="Wukong";perso[146][1]="Male";perso[146][2]="Top";perso[146][3]="Shimon";perso[146][4]="Mana";perso[146][5]="Melee";perso[146][6]="Ionia";perso[146][7]="2011";
	perso[147][0]="Xayah";perso[147][1]="Female";perso[147][2]="Bottom";perso[147][3]="Vastayan";perso[147][4]="Mana";perso[147][5]="Ranged";perso[147][6]="Ionia";perso[147][7]="2017";
	perso[148][0]="Xerath";perso[148][1]="Male";perso[148][2]="Middle";perso[148][3]="Baccai";perso[148][4]="Mana";perso[148][5]="Ranged";perso[148][6]="Shurima";perso[148][7]="2011";
	perso[149][0]="Xin Zhao";perso[149][1]="Male";perso[149][2]="Jungle";perso[149][3]="Human";perso[149][4]="Mana";perso[149][5]="Melee";perso[149][6]="Demacia";perso[149][7]="2010";
	perso[150][0]="Yasuo";perso[150][1]="Male";perso[150][2]="Top";perso[150][3]="Human";perso[150][4]="Flow";perso[150][5]="Melee";perso[150][6]="Ionia";perso[150][7]="2013";
	perso[151][0]="Yone";perso[151][1]="Male";perso[151][2]="Middle";perso[151][3]="Human";perso[151][4]="Manaless";perso[151][5]="Melee";perso[151][6]="Ionia";perso[151][7]="2020";
	perso[152][0]="Yorick";perso[152][1]="Male";perso[152][2]="Top";perso[152][3]="Human";perso[152][4]="Mana";perso[152][5]="Melee";perso[152][6]="Shadow Isles";perso[152][7]="2011";
	perso[153][0]="Yuumi";perso[153][1]="Female";perso[153][2]="Support";perso[153][3]="Cat";perso[153][4]="Mana";perso[153][5]="Ranged";perso[153][6]="Bandle City";perso[153][7]="2019";
	perso[154][0]="Zac";perso[154][1]="Male";perso[154][2]="Jungle";perso[154][3]="Golem";perso[154][4]="Healthcosts";perso[154][5]="Melee";perso[154][6]="Zaun";perso[154][7]="2013";
	perso[155][0]="Zed";perso[155][1]="Male";perso[155][2]="Middle";perso[155][3]="Human";perso[155][4]="Energy";perso[155][5]="Melee";perso[155][6]="Ionia";perso[155][7]="2012";
	perso[156][0]="Zeri";perso[156][1]="Female";perso[156][2]="Bottom";perso[156][3]="Human";perso[156][4]="Mana";perso[156][5]="Ranged";perso[156][6]="Zaun";perso[156][7]="2022";
	perso[157][0]="Ziggs";perso[157][1]="Male";perso[157][2]="Middle";perso[157][3]="Yordle";perso[157][4]="Mana";perso[157][5]="Ranged";perso[157][6]="Zaun";perso[157][7]="2012";
	perso[158][0]="Zilean";perso[158][1]="Male";perso[158][2]="Support";perso[158][3]="Human";perso[158][4]="Mana";perso[158][5]="Ranged";perso[158][6]="Runeterra";perso[158][7]="2009";
	perso[159][0]="Zoe";perso[159][1]="Female";perso[159][2]="Middle";perso[159][3]="Aspect";perso[159][4]="Mana";perso[159][5]="Ranged";perso[159][6]="Targon";perso[159][7]="2017";
	perso[160][0]="Zyra";perso[160][1]="Female";perso[160][2]="Support";perso[160][3]="Unknown";perso[160][4]="Mana";perso[160][5]="Ranged";perso[160][6]="Ixtal";perso[160][7]="2012";
	return(perso[rand][stat]);
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_reset(void)
{
	for (size_t y = 0; y < VGA_HEIGHT-1; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = terminal_buffer[index+VGA_WIDTH];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++){
		terminal_buffer[(VGA_HEIGHT-1)*VGA_WIDTH + x] = vga_entry(' ', terminal_color);
	}
	terminal_row += -1;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_delete(void)
{
	if (terminal_column>0)
	{
		terminal_column+= -1;
		const size_t index = terminal_row * VGA_WIDTH + terminal_column;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
		
	}
	/* pour edit de texte et que le del remonte des ligne else
	{
		terminal_row+=-1;
		bool pasfin=true;
		for (int x=VGA_WIDTH-1; x>=0; x+=-1)
			{if (pasfin && terminal_buffer[terminal_row * VGA_WIDTH + x]!=vga_entry(' ', terminal_color)) {
				pasfin=false;
				terminal_column=x+1;
			}}
	}
	*/
}

void terminal_putchar(char c) 
{
	if (c=='\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
				terminal_reset();
				}
	}
	else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
		}
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

size_t get_terminal_row(void){
	return(terminal_row);
}
void set_terminal_row(size_t r){
	terminal_row=r;
}

size_t get_terminal_column(void){
	return(terminal_column);
}
void set_terminal_column(size_t r){
	terminal_column=r;
}

void set_terminal_buffer(size_t index, uint16_t col){
	terminal_buffer[index]=col;
}

size_t get_height(void){
	return(VGA_HEIGHT);
}

size_t get_width(void){
	return(VGA_WIDTH);
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

uint8_t get_terminal_color(void){
	return(terminal_color);
}

uint8_t get_entry_color(size_t fc, size_t bc){
	return(vga_entry_color(fc,bc));
} 
