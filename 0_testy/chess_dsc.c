//Kod przepisany z wykładu :)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/*
Gracz
0 król,
1 hetman,
2 wieza,
3 goniec,
4 skoczek
5 pionek

Komputer
6 król
7 hetman
8 wieza
9 goniec
10 skoczek
11 pionek
12 puste pole

*/


int MAX_KIER[]={8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_ODL[]={2,8,8,8,2,2,2,8,8,8,2,2,0};

int WX[12][8]={{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1},{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1} };

int WY[12][8]={{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{-1,-1,-1},{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1} };


char plansza[8][8]={
8,	11, 12, 12, 12, 12, 5, 2,
10,	11, 12, 12, 12, 12, 5, 4,
9,	11, 12, 12, 12, 12, 5, 3,
6,	11, 12, 12, 12, 12, 5, 1,
7,	11, 12, 12, 12, 12, 5, 0,
9,	11, 12, 12, 12, 12, 5, 3,
10,	11, 12, 12, 12, 12, 5, 4,
8,	11, 12, 12, 12, 12, 5, 2,
};

int ocena(){
	int i, j, w=0;
	int oc[]={-1000, -9, -5, -4, -3, -1, 1000, 9, 5, 4, 3, 1, 0};
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			w+=oc[plansza[i][j]];
	return w;
}


void wypisz(){
	char fig[]="khwgspKHWGSP ";
	printf("\n\n\n========================================\n");
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++)
			printf("| %c |", fig[plansza[i][j]]);
		printf("\n========================================\n");
	}

}


int najlepszy(int tryb, int *x, int *y, int *k, int *o){
	int px_pom, py_pom, k_pom, o_pom, px_py, px, py, dx, dy, kierunek, odleglosc;
	int wynik, wmax, wmin, ruch_fig, bita_fig;

	wynik=ocena();
	if(tryb == 0 || 2*wynik>1000 || 2*wynik<-1000) return wynik;
	if(tryb%2==0){//komputer
		for(px=0,wmax=100*-1000;px<8;px++)
			for(py=0;py<8;py++)
                if(plansza[px][py]>=6 && plansza[px][py]<12) //sprawdzenie czy na polu [px][py] znajduje sie figura komputera
				for(kierunek=0;kierunek<MAX_KIER[plansza[px][py]];kierunek++)
					for(odleglosc=1;odleglosc<MAX_ODL[plansza[px][py]];odleglosc++){
						dx=(odleglosc-1)*WX[plansza[px][py]][kierunek];
						dy=(odleglosc-1)*WY[plansza[px][py]][kierunek];

						if(odleglosc>=2 && plansza[px+dx][py+dy]!=12) break; //jesli po drodze niepuste
						dx=odleglosc*WX[plansza[px][py]][kierunek];
						dy=odleglosc*WY[plansza[px][py]][kierunek];

						if(px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8) //ruch w szachownicy
							if(plansza[px+dx][py+dy]==12 || plansza[px+dx][py+dy]<=5){ //pole końcowe puste/fig wroga
								if(plansza[px][py]!=11 || (plansza[px+dx][py+dy] == 12 && dx==0) || (plansza[px+dx][py+dy]!=12 && dx!=0)){
									ruch_fig=plansza[px][py];
									bita_fig=plansza[px+dx][py+dy];
									plansza[px+dx][py+dy]=plansza[px][py];
									plansza[px][py]=12;

									if(plansza[px+dx][py+dy]==11 && py+dy==7)
										plansza[px+dx][py+dy]=7;
									wynik=najlepszy(tryb-1, &px_pom, &py_pom, &k_pom, &o_pom);
									plansza[px][py] = ruch_fig; //cofniecie ruchu
									plansza[px+dx][py+dy]=bita_fig;
									if(wynik>=wmax){wmax=wynik;*x=px,*y=py, *k=kierunek, *o=odleglosc;}
								}
							}
					}
	return wmax;
	}
	else{//gracz
		for(px=0,wmin=100*1000;px<8;px++)
			for(py=0;py<8;py++)
             if(plansza[px][py]>=0 && plansza[px][py]<6) //sprawdzenie czy na polu [px][py] znajduje sie figura gracza
				for(kierunek=0;kierunek<MAX_KIER[plansza[px][py]];kierunek++)
					for(odleglosc=1;odleglosc<MAX_ODL[plansza[px][py]];odleglosc++){
						dx=(odleglosc-1)*WX[plansza[px][py]][kierunek];
						dy=(odleglosc-1)*WY[plansza[px][py]][kierunek];

						if(odleglosc>=2 && plansza[px+dx][py+dy]!=12) break; //jesli po drodze niepuste
						dx=odleglosc*WX[plansza[px][py]][kierunek];
						dy=odleglosc*WY[plansza[px][py]][kierunek];

						if(px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8) //ruch w szachownicy
							if(plansza[px+dx][py+dy]==12 || plansza[px+dx][py+dy]>=6){ //pole końcowe puste/fig wroga
								if(plansza[px][py]!=5 || (plansza[px+dx][py+dy] == 12 && dx==0) || (plansza[px+dx][py+dy]!=12 && dx!=0)){
									ruch_fig=plansza[px][py];
									bita_fig=plansza[px+dx][py+dy];
									plansza[px+dx][py+dy]=plansza[px][py];
									plansza[px][py]=12;

									if(plansza[px+dx][py+dy]==5 && py+dy==0)
										plansza[px+dx][py+dy]=1;
									wynik=najlepszy(tryb-1, &px_pom, &py_pom, &k_pom, &o_pom);
									plansza[px][py] = ruch_fig; //cofniecie ruchu
									plansza[px+dx][py+dy]=bita_fig;
									if(wynik<=wmin){wmin=wynik;*x=px,*y=py, *k=kierunek, *o=odleglosc;}
								}
							}
                        if (plansza[px+dx][py+dy]!=12) break;
					}
	return wmin;
	}
}



int main(){
	int x, y, wyn, k, o, dx, dy, x2, y2;
	while(1){
		najlepszy(4, &x, &y, &k, &o);
		dx=o*WX[plansza[x][y]][k];
		dy=o*WY[plansza[x][y]][k];
		plansza[x+dx][y+dy]=plansza[x][y];
		plansza[x][y]=12;
		if(plansza[x+dx][y+dy]==11 && y+dy==7) plansza[x+dx][y+dy]=7;
		wypisz();
		if(ocena()>=1000) {printf("Komputer wygral!"); return 0;}
		else if(ocena()<=-1000){printf("Wygrales!"); return 0;}
		printf("podaj ruch skad dokad");
		scanf("%d%d%d%d", &x, &y, &x2, &y2);
		plansza[x2][y2]=plansza[x][y];
		plansza[x][y]=12;
		if(plansza[x2][y2]==5 && y2==0) plansza[x2][y2]=1;
		wypisz();
		if(ocena()>=1000) {printf("Komputer wygral!"); return 0;}
		else if(ocena()<=-1000){printf("Wygrales!"); return 0;}
	}
    return 0;
}