#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "agent.h"
#include "experiment.h"
#include "activity.h"
#include "dataFile.h"
#include "project.h"
#include "menu.h"


void secondMenu(){
	int answer = -1;
	while(answer != 99){
		printf("\n\t\t*---- MAIN MENU ----* ");
		printf("\n\t0 - Run all commands");
		printf("\n\t1 - hisat2-build *.fa --snp *.snp *M");
		printf("\n\t2 - hisat2 -f -x *_snp -U *.fa -S *.sam");
		printf("\n\t3 - head *.sam");
		printf("\n\t4 - samtools view -bS *.sam > *.bam");
		printf("\n\t5 - samtools sort -n *.bam *_sorted.sn");
		printf("\n\t6 - samtools view -h -o *_sorted.sn.sam *.bam");
		printf("\n\t7 - htseq -m intersection-nonempty -s -no *_sorted.sn.sam *.gtf : *.counts");
		printf("\n\t99 - Return");
		printf("\n\n...");
		scanf("%d", &answer);
		switch(answer){
			case 0: 
				//runAll();
			break;
			case 1: 
				//command1();
			break;
			case 2: 
				//command2();
			break;
			case 3: 
				//command3();
			break;
			case 4: 
				//command4();
			break;
			case 5: 
				//command5();
			break;
			case 6: 
				//command6();
			break;
			case 7: 
				//command7();
			break;
			case 99: 
				mainMenu();
			break;
			default:
			break;

		}
	}
}

void mainMenu (){
	int answer = 0;
	while(answer != 99){
		printf("\n\t\t*---- MAIN MENU ----* ");
		printf("\n\t1 - Execute defined commands");
		printf("\n\t2 - Test");
		printf("\n\t99 - Exit");
		printf("\n\n...");
		scanf("%d", &answer);
		switch(answer){
			case 1: 
				secondMenu();
			break;
			case 2: 

			break;
			case 99: 
				printf("\n");
			break;
			default:
			break;

		}
	}
}
