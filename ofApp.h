/************************************************************
description
	fileを順次 読み込んでapp内部で使用.
	openframeworksにofBufferと言うのがあったが、イマイチわかりにくく、直に触った方が安全と判断し、本sampleを作成.
	
改行Codeについて
	一般に、以下のように、場合によって改行Codeは異なる。
		Unix	LF		0x0A(\n)
		win		CR/LF	0x0D(\r)/ 0x0A(\n)
		max		CR		0x0D(\r)
		
	
	しかし、話はあまり単純でなく、
	OS, app(Excel経由で保存すると、改行 = CR/LFになる), compilerで改行Codeは異なるし、
	あるOSでも、その上で走るappによって保存fileの改行Codeは異なる。
	また、fopenにおけるr, rbなどのoptionによって、差異を吸収してくれる、と記述があるが、
	実際に読み込んでみると吸収していなかったり・・・
	
	正直、これをまとめて、覚えるよりも、以下のように、都度、確認するのがGood.
	つまり結論としては、
	都度、
	使用するFileについて(fprintでoutしたものにせよ、別appで作成したものにせよ)、
	使用するoptionにて読み込みを行い、
		for(int i = 0; i < strlen(buf); i++){
			printf("[%02X]\n", buf[i]);
		}
	としてCodeをcheckするのが良い.
	その上で、適切に(改行を削除するとか・・・)処理を行えばOK.
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	/********************
	********************/
	enum{
		WINDOW_WIDTH	= 200,
		WINDOW_HEIGHT	= 200,
	};
	enum{
		MAX_BUFSIZE = 10000,
	};
	
	/****************************************
	****************************************/
	FILE* fp_out;
	FILE* fp_in;
	
	/****************************************
	****************************************/
	void OutToFile();
	void Align(string& s);
	void YennToCR(string& s);
	string CR_To_Yenn(string s);
	
	bool checkIf_ContentsExist(char* ret, char* buf);
	
public:
	/****************************************
	****************************************/
	/********************
	********************/
	void exit();
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
