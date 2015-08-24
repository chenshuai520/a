/*
* "Shape Context" descriptor code (by Krystian Mikolajczyk <http://personal.ee.surrey.ac.uk/Personal/K.Mikolajczyk> ) based on SIFT (by David Lowe)
*
* This code is granted free of charge for non-commercial research and
* education purposes. However you must obtain a license from the author
* to use it for commercial purposes.

* The software and derivatives of the software must not be distributed
* without prior permission of the author.
*
*  If you use this code you should cite the following paper:
*  K. Mikolajczyk, C. Schmid,  A performance evaluation of local descriptors. In PAMI 27(10):1615-1630
*/

// Implementation de la classe image
//
#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>

#include <libFilesystemAux/filesystem_aux.h>
#include <libBoostMath/boost_math.h>  //-- [] 2012/08/07: Sang-Wook Lee

#include "imageContent.h"

#define png_voidp_NULL            (png_voidp)NULL  //-- [] 2012/08/07: Sang-Wook Lee
#define png_infopp_NULL (png_infopp)NULL  //-- [] 2012/07/24: Sang-Wook Lee

using namespace std;
using namespace kma;

float ImageContent::getValue(float x, float y){

  unsigned int ix=(unsigned int)floor(x);
  unsigned int iy=(unsigned int)floor(y);
  float dx = x-ix;
  float dy = y-iy; 
  float val=0;
  //if(ix>=0 && iy>=0 && ix<x_size-1 && iy<y_size-1){
  if(ix<x_size-1 && iy<y_size-1){
    val =  (1.0 - dy)*((1.0 - dx)*fel[iy][ix] +
		       dx*fel[iy][ix+1]) +
      dy*((1.0 - dx)*fel[iy+1][ix] +
	  dx *fel[iy+1][ix+1]);    
  } else if(ix==(x_size-1) && iy<y_size-1){
    val= (1.0 - dy)*fel[iy][ix] +
      dy*(fel[iy+1][ix]);
  }else if(iy==(y_size-1) && ix<x_size-1){
    val= (1.0 - dx)*fel[iy][ix] +
      dx*(fel[iy][ix+1]);
  }else if(iy==(y_size-1) && ix==(x_size-1)){
    val = fel[iy][ix];
  }else val=0;
  return val;
}



/****************************************************************/
int kma::verif_format(const char* name)
{


  FILE* ident;
  //char *buf1 = new char[2];
  unsigned char buf1[PNG_BYTES_TO_CHECK];

 if((  ident = fopen(name,"r") ) == NULL) {cout  << "Unable to open " << name << endl;   return(0); }
 
 fread(buf1,1,PNG_BYTES_TO_CHECK,ident);
 fclose(ident);
 
 if(!png_sig_cmp(&buf1[0], (png_size_t)0, PNG_BYTES_TO_CHECK))return(4);
 else if((buf1[0]) != 'P')  return(0);
 else if(buf1[1] == '5') return(1);
 else if( buf1[1] == 'g' ) return(2);
 else if(buf1[1] == '6' ) return(3);
 
  return 0; 
}

/****************************************************************/
ImageContent::ImageContent(uint y_size_in,uint x_size_in, const char *s)
{
  if(!strcmp("uchar",s)){ 
    initUChar( y_size_in, x_size_in);   
  }else if(!strcmp("float",s)){
    initFloat( y_size_in, x_size_in); 
  }else if(!strcmp("3uchar",s)){
    init3UChar( y_size_in, x_size_in); 
  }else if(!strcmp("3float",s)){
    init3Float( y_size_in, x_size_in); 
  }

}
/****************************************************************/
ImageContent::ImageContent(ImageContent *im){
  if(im->getType()==2)initFloat(im->y(),im->x());    
  else if(im->getType()==1)initUChar(im->y(),im->x());  
  set(im);
}	   

/****************************************************************/
ImageContent::ImageContent(uint y_size_in,uint x_size_in, const char *s, float value)
{
  if(!strcmp("uchar",s)){ 
    initUChar( y_size_in, x_size_in);     
  }else if(!strcmp("float",s)){
    initFloat( y_size_in, x_size_in); 
  }else if(!strcmp("3uchar",s)){
    init3UChar( y_size_in, x_size_in); 
  }else if(!strcmp("3float",s)){
    init3Float( y_size_in, x_size_in); 
  }
  set(value);
}


/****************************************************************/
void ImageContent::initFloat(uint y_size_in,uint x_size_in)
{
        filename = new char[100];
	x_size=x_size_in;
	y_size=y_size_in;
	tsize=y_size*x_size;
	fel = new float*[y_size];
	fel[0]=new float[tsize];
	for(uint i=1;i<y_size;i++)fel[i]=fel[0]+i*x_size;  
	buftype=FLOAT;	

}

/****************************************************************/
void ImageContent::initUChar(uint y_size_in,uint x_size_in)
{
        filename = new char[100];
	x_size=x_size_in;
	y_size=y_size_in;
	tsize=y_size*x_size;
	bel = new unsigned char*[y_size];
	bel[0]=new unsigned char[tsize];
	for(uint i=1;i<y_size;i++)bel[i]=bel[0]+i*x_size;  
	buftype=UCHAR;	
}

/****************************************************************/
void ImageContent::init3UChar(uint y_size_in,uint x_size_in)
{
        filename = new char[100];
	x_size=x_size_in;
	y_size=y_size_in;
	tsize=y_size*x_size;

	belr = new unsigned char*[y_size];
	belr[0]=new unsigned char[tsize];
	for(uint i=1;i<y_size;i++)belr[i]=belr[0]+i*x_size;  

	belg = new unsigned char*[y_size];
	belg[0]=new unsigned char[tsize];
	for(uint i=1;i<y_size;i++)belg[i]=belg[0]+i*x_size;  

	belb = new unsigned char*[y_size];
	belb[0]=new unsigned char[tsize];
	for(uint i=1;i<y_size;i++)belb[i]=belb[0]+i*x_size;  
	buftype=CUCHAR;	

}

/****************************************************************/
void ImageContent::init3Float(uint y_size_in,uint x_size_in)
{
        filename = new char[100];
	x_size=x_size_in;
	y_size=y_size_in;
	tsize=y_size*x_size;

	felr = new float*[y_size];
	felr[0]=new float[tsize];
	for(uint i=1;i<y_size;i++)felr[i]=felr[0]+i*x_size;  

	felg = new float*[y_size];
	felg[0]=new float[tsize];
	for(uint i=1;i<y_size;i++)felg[i]=felg[0]+i*x_size;  

	felb = new float*[y_size];
	felb[0]=new float[tsize];
	for(uint i=1;i<y_size;i++)felb[i]=felb[0]+i*x_size;  

	buftype=CFLOAT;	

}


/****************************************************************/
void ImageContent::set(float val)
{
  if(buftype==FLOAT){
    if(val==0.0){
	  //--S [] 2012/07/24: Sang-Wook Lee
      //bzero(fel[0],tsize*sizeof(float));
      memset(fel[0], 0, tsize*sizeof(float));
	  //--E [] 2012/07/24
    }else
      for (uint col = 0; col < tsize; col++){
	fel[0][col] = val;
      }    
  }
  else if(buftype==UCHAR){
    unsigned char value = (unsigned char)val;
    memset(bel[0],(int)value,tsize*sizeof(unsigned char));
  }
}

/****************************************************************/
void ImageContent::flipH()
{
  if(buftype==FLOAT){
    float tmp;
    uint middle=(x_size>>1);
   for (uint row = 0; row < y_size; row++){
      for (uint col = 0; col <= middle; col++){
	tmp=fel[row][col];
	fel[row][col]=fel[row][x_size-1-col];
	fel[row][x_size-1-col]=tmp;
      }    
    }   
   
  }else if(buftype==UCHAR){
    unsigned char btmp;
    uint middle=(x_size>>1);
    for (uint row = 0; row < y_size; row++){
      for (uint col = 0; col <= middle; col++){
	btmp=bel[row][col];
	bel[row][col]=bel[row][x_size-1-col];
	bel[row][x_size-1-col]=btmp;
      }    
    }       
  }
}
/****************************************************************/
void ImageContent::flipV()
{
  if(buftype==FLOAT){
    float tmp;
    uint middle=(y_size>>1);
   for (uint col = 0; col < x_size; col++){
     for (uint row = 0; row <= middle; row++){
       tmp=fel[row][col];
       fel[row][col]=fel[y_size-1-row][col];
       fel[y_size-1-row][col]=tmp;
     }    
   }   
   
  }else if(buftype==UCHAR){
    unsigned char btmp;
    uint middle=(y_size>>1);
   for (uint col = 0; col < x_size; col++){
     for (uint row = 0; row <= middle; row++){
       btmp=bel[row][col];
       bel[row][col]=bel[y_size-1-row][col];
       bel[y_size-1-row][col]=btmp;
     }    
   }   
  }
}

/****************************************************************/
void ImageContent::set(ImageContent *im)
{
  if(im->size()!=tsize){
    cout << "error: different image size"<< endl;return;  
  }
  if(im->getType()==UCHAR && buftype==UCHAR){
    memcpy(bel[0],im->bel[0],tsize*sizeof(unsigned char)); 
  }else if(im->getType()==FLOAT && buftype==FLOAT)
    memcpy(fel[0],im->fel[0],tsize*sizeof(float));
  else if(im->getType()==UCHAR && buftype==FLOAT)
    for (uint col = 0; col < tsize; col++){
      fel[0][col] = (float)im->bel[0][col];
    }  
  else if(im->getType()==FLOAT && buftype==UCHAR)
    for (uint col = 0; col < tsize; col++){
      bel[0][col] = (unsigned char)im->fel[0][col];
    }  
}


/****************************************************************/
ImageContent::ImageContent(const char *name)
{
  int type;

  type =  kma::verif_format(name);
  //  cout << type << endl;
  if(type ==0){
      cerr  << "unrecognize image format: " << name << endl;
  }else if(type ==4){

    png_structp png_ptr;
    png_infop info_ptr;
    
    FILE *fp = fopen(name, "rb");
    if(fp == NULL)return;

    unsigned char buf[PNG_BYTES_TO_CHECK];
    if ((int)fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
      return;
    if(png_sig_cmp(&buf[0], (png_size_t)0, PNG_BYTES_TO_CHECK))return;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
      fclose(fp);
      return;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
      fclose(fp);
      png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
      return;
    }    

    if (setjmp(png_jmpbuf(png_ptr))) {
      png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
      fclose(fp);
      return;
    }    
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);

    int bit_depth, pix_channels, color_type;
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);
    x_size = (uint)png_get_image_width(png_ptr, info_ptr);
    y_size = (uint)png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    pix_channels = png_get_channels( png_ptr,  info_ptr);
    color_type=png_get_color_type(png_ptr, info_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
      png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) 
	  //--S [] 2012/08/07: Sang-Wook Lee
      //png_set_gray_1_2_4_to_8(png_ptr);
      png_set_expand_gray_1_2_4_to_8(png_ptr);
	  //--E [] 2012/08/07
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) 
      png_set_tRNS_to_alpha(png_ptr);
    
    fclose(fp);
    
    if(color_type!=PNG_COLOR_TYPE_GRAY && color_type!=PNG_COLOR_TYPE_RGB){
      cout << "Attention! strange color type "<< color_type << endl;
      
    }
  
    png_bytep *src_rows;
    src_rows = png_get_rows(png_ptr, info_ptr);
    
    if(pix_channels==1){
      initUChar(y_size,x_size);
      for(uint row = 0; row < y_size; row++) {
	for(uint col = 0; col < x_size; col++) {
	  bel[row][col] = src_rows[row][col];
	}
      }
      buftype=UCHAR;
    }else if(pix_channels==3){
      init3UChar(y_size,x_size);
       for(uint row = 0; row < y_size; row++) {
	 for(uint col = 0, k=0; col < x_size; col++) {
	  belr[row][col] = src_rows[row][k++] ;
	  belg[row][col] = src_rows[row][k++] ;
	  belb[row][col] = src_rows[row][k++] ;	    
	}  
       }    
      buftype=CUCHAR;        
    }
 
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
    
  }else{
    ifstream image(name);
	char *buf1;
	char* bigbuf;

	buf1 = new char[4];
	bigbuf = new char [512];
	image >> buf1;
	image >> buf1;
	while( buf1[0] == '#') {  image.getline(bigbuf,512);  image >> buf1; } // skipping the comments

	 x_size = atoi(buf1);
	 image >>  buf1; 
	 y_size = atoi(buf1);

	image >> buf1; // number of graylevels
	image.getline(bigbuf,512);
	
	if(type ==1 || type ==2){
	  initUChar(y_size,x_size);	  
	  image.read((char*)bel[0],tsize);
	  buftype=UCHAR;
	}else if(type == 3){
	  init3UChar(y_size,x_size);
	  unsigned char *buff = new unsigned char [3*tsize];	  
	  image.read((char*)buff,3*tsize);
	  for (uint k = 0, i = 0 ; i <tsize ; i++){
	    belr[0][i] = buff[k++] ;
	    belg[0][i] = buff[k++] ;
	    belb[0][i] = buff[k++] ;	    
	  }
	    
	  buftype=CUCHAR;
	  delete [] buff;
	}
	delete [] buf1;
	delete [] bigbuf;
	    
	image.close();
  }
}

/****************************************************************/
// Ecriture d'une Image 
void ImageContent::write(const char* name){
    write(name,"# comments");

}


void ImageContent::writePNG(const char* name){
  if(buftype==0)return;
  
  float2char();
  png_structp png_ptr;
  png_infop info_ptr;
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL){cout << "png_create_write_struct error...  " << endl;exit(0);}
  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) {
    png_destroy_write_struct(&png_ptr, png_infopp_NULL);
    cout << "png_create_info_struct error...  " << endl;exit(0);
  }
  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    cout << "setjmp error...  " << endl;exit(0);
  }
  
  FILE *fp = fopen(name, "wb");
  if(fp == NULL)return;
  png_init_io(png_ptr, fp);
  int bit_depth=8;
  
  if(buftype==UCHAR || buftype==UCHARFLOAT){
    png_set_IHDR(png_ptr, info_ptr, x_size, y_size, bit_depth, PNG_COLOR_TYPE_GRAY,
		 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_set_rows(png_ptr, info_ptr, bel);
    //png_write_info(png_ptr, info_ptr);
    //png_write_image(png_ptr, bel);
    //png_write_end(png_ptr, info_ptr);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);
    //cout << "OK2 wrote " << buftype << endl;
  
    if(buftype==UCHARFLOAT){
      delete[] bel[0];delete[] bel;
      buftype=FLOAT;
    }
  }
  if(buftype==CUCHAR || buftype==CUCHARFLOAT){
    png_set_IHDR(png_ptr, info_ptr, x_size, y_size, bit_depth, PNG_COLOR_TYPE_RGB,
		 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    
    
    unsigned char **bell = new unsigned char*[y_size];
    bell[0]=new unsigned char[3*tsize];
    for(uint i=1;i<y_size;i++)bell[i]=bell[0]+i*3*x_size;  	
 
    for (uint row = 0; row <y_size ; row++){
      for (uint col = 0, k = 0 ; col <x_size ; col++){
	bell[row][k++]=belr[row][col];
	bell[row][k++]=belg[row][col];
	bell[row][k++]=belb[row][col];
      }
    }
    png_set_rows(png_ptr, info_ptr, bell);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);
    delete [] bell[0];delete []  bell;bell=NULL;

    
    
    if(buftype==CUCHARFLOAT){
      delete [] belr[0];delete []  belr;belr=NULL;
      delete [] belg[0];delete []  belg;belg=NULL;
      delete [] belb[0];delete []  belb;belb=NULL;
      buftype=CFLOAT;
    }
  }
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
}


void ImageContent::write(const char* name,const char* comments)
{ 
  if(buftype==0)return;
  
  float2char();
  
  if(buftype==UCHAR || buftype==UCHARFLOAT){    
    writePGM(name, bel[0], comments);
    if(buftype==UCHARFLOAT){
      delete[] bel[0];delete[] bel;
      buftype=FLOAT;
    }
  }
  if(buftype==CUCHAR || buftype==CUCHARFLOAT){
    ofstream theexit (name);
    if( !theexit)  { cerr << "Enable to open " << name << endl;   return;}
    
    theexit <<"P6"<<endl; 
    theexit << "# "<< comments <<endl;
    theexit << x_size << " " << y_size << endl;
    theexit << "255" << endl;
    
    unsigned char *buff = new unsigned char [3*tsize];
    for (uint k = 0, i = 0 ; i <tsize ; i++){
      buff[k++]=belr[0][i];
      buff[k++]=belg[0][i];
      buff[k++]=belb[0][i];
    }
    theexit.write((char *)buff,3*tsize);
    theexit.close();
    delete []buff;
    if(buftype==CUCHARFLOAT){
      delete [] belr[0];delete []  belr;belr=NULL;
      delete [] belg[0];delete []  belg;belg=NULL;
      delete [] belb[0];delete []  belb;belb=NULL;
      buftype=CFLOAT;
    }
  }
}

void ImageContent::writeR(const char* name){
  writePGM(name,belr[0],"");  
}
void ImageContent::writeG(const char* name){
  writePGM(name,belg[0],"");
}
void ImageContent::writeB(const char* name){
  writePGM(name,belb[0],"");
}


void ImageContent::writePGM(const char* name, unsigned char* buff, const char* comments){
  if(buftype==0)return;
  
  float2char();
  
  if(buftype==CUCHAR || buftype==CUCHARFLOAT || buftype==UCHAR || buftype==UCHARFLOAT){
    ofstream theexit(name);
    if( !theexit)  { cerr << "Enable to open " << name << endl;   return;}
    
    theexit <<"P5"<<endl; 
    theexit << "# " << comments <<endl;
    theexit << x_size << " " << y_size << endl;
    theexit << "255" << endl; 
    
    theexit.write((char*)buff,tsize);
    theexit.close();
  }
}

void ImageContent::RGB2xyY(){
  if(buftype==CFLOAT && buftype==CUCHARFLOAT){
    cout << " wrong buftype - convert to float"<< endl;
    return;
  }
  for(uint i=0;i<tsize;i++){
     felr[0][i]/=255.0;//norm(inverse_gamma_correction(rgb->fel3[j][i]));
      felg[0][i]/=255.0;//norm(inverse_gamma_correction(rgb->fel2[j][i]));
      felb[0][i]/=255.0;//norm(inverse_gamma_correction(rgb->fel1[j][i]));  
  }
  
  float r,g,b;
  float sum;
  for (uint i = 0 ; i < tsize ; i++){
      r=felr[0][i];
      g=felg[0][i];
      b=felb[0][i];
      felr[0][i] =0.412453 * r + 0.357580 * g + 0.180423 * b ;
      felg[0][i] =0.212671 * r + 0.715160 * g + 0.072169 * b ;
      felb[0][i] =0.019334 * r + 0.119193 * g + 0.950227 * b ;
      sum=felr[0][i]+felg[0][i]+felb[0][i];
      if(sum!=0){
	felr[0][i] /= sum ;
	felg[0][i] = felg[0][i];
	felb[0][i] /= sum ;
      }
  }
}

void ImageContent::RGB2lbrg(){
  if(buftype==CFLOAT && buftype==CUCHARFLOAT){
    cout << " wrong buftype - convert to float"<< endl;
    return;
  }
  float r,g,b,lg,lr,lb;
  for(uint i=0;i<x_size;i++){
    for(uint j=0;j<y_size;j++){
      r=felr[j][i];
      g=felg[j][i];
      b=felb[j][i];
      lr=(g==0)?0:log(r);
      lg=(g==0)?0:log(g);
      lb=(b==0)?0:log(b);
      felb[j][i]=lg/5.55;
      felg[j][i]=(lr-lg+5.55)/11.1;
      felr[j][i]=((lb-(lg+lr)/2.0)+5.55)/11.1;	    
    }
  }
}
void ImageContent::RGB2rgb(){
  if(buftype==CFLOAT && buftype==CUCHARFLOAT){
    cout << " wrong buftype - convert to float"<< endl;
    return;
  }
  float sum;
  for(uint i=0;i<x_size;i++){
    for(uint j=0;j<y_size;j++){
      sum=felr[j][i]+felg[j][i]+felb[j][i];
      if(sum!=0){
	felb[j][i]/=sum;//norm(inverse_gamma_correction(rgb->fel3[j][i]));
	felg[j][i]/=sum;//norm(inverse_gamma_correction(rgb->fel2[j][i]));
	felr[j][i]/=sum;//norm(inverse_gamma_correction(rgb->fel1[j][i]));  
      }
    }
  }
}

/****************************************************************/
void ImageContent::char2float()
{
  if(buftype==UCHAR){
    initFloat(y_size,x_size); 
    for (uint col = 0; col < tsize; col++){
      fel[0][col] = (float)bel[0][col];
    } 
    delete []  bel[0];delete []  bel;
    buftype=FLOAT;
  }
}

/****************************************************************/
void ImageContent::interpolate(DARY *im_in, float m_x, float m_y, 
				 float scalex, float scaley, 
				 float angle){
    float lecos = cos(2*M_PI*angle/360);
    float lesin = sin(2*M_PI*angle/360);	        
    float vec0x = (1.0/scalex)*lecos; 
    float vec0y = (1.0/scaley)*lesin;
    float vec1x = -lesin*(1.0/scalex);
    float vec1y = lecos*(1.0/scaley);
    interpolate(im_in, m_x, m_y, vec0x , vec0y  ,vec1x ,vec1y);
}

/****************************************************************/
void ImageContent::interpolate(DARY *im_in, float m_x, float m_y, float vec0x, float vec0y,
			       float vec1x, float vec1y){
    float px, py, dx, dy;
    int arondx, arondy;
    int width_2  = x_size>>1;
    int height_2 = y_size>>1;

    /** problem: images with even number of rows/columns have last line not filled during interpolation */
    //if(!(x_size%2))width_2--;
    //if(!(y_size%2))height_2--;

    /** fix: */
    int minx = -width_2;
    int maxx = width_2;
    int miny = -height_2;
    int maxy = height_2;

    if (x_size % 2 == 0)
      --maxx;
    
    if (y_size % 2 == 0)
      --maxy;

    int xim_in = im_in->x()-1;
    int yim_in = im_in->y()-1;

    //printf("interpolate, x_size: %d, y_size: %d\n", x_size, y_size);
    //printf("interpolate, width_2: %d, height_2: %d\n", width_2, height_2);

    for(int j=miny; j<=maxy; j++){
      for(int i=minx; i<=maxx; i++){

    //for(int j=-height_2;j<=height_2; j++){
    //  for(int i=-width_2;i<=width_2; i++){
        //printf("\tinterpolate, ypos: %d, xpos: %d\n", j+height_2, i+width_2);

	px = m_x + i*vec0x + j*vec0y;
	py = m_y + i*vec1x + j*vec1y;
	    arondx = (int) floor(px);
	    arondy = (int) floor(py);
	    dx = px -  arondx;
	    dy = py -  arondy;     
	    if(arondx>=0 && arondy>=0 && arondx<xim_in && arondy<yim_in){
		fel[j+height_2][i+width_2] = 
		    ((1.0 - dy)*((1.0 - dx)*im_in->fel[arondy][arondx] +
				 dx*im_in->fel[arondy][arondx+1]) +
		     dy*((1.0 - dx)*im_in->fel[arondy+1][arondx] +
			 dx *im_in->fel[arondy+1][arondx+1]));
	    }else if(arondx<0 && arondy<0){
	      fel[j+height_2][i+width_2]= im_in->fel[0][0];
	    } else if(arondx>=xim_in && arondy>=yim_in){
	      fel[j+height_2][i+width_2]= im_in->fel[yim_in][xim_in];
	    } else if(arondx<0 && arondy>yim_in){
	      fel[j+height_2][i+width_2]= im_in->fel[yim_in][0];
	    } else if(arondx>=xim_in && arondy<0){
	      fel[j+height_2][i+width_2]= im_in->fel[0][xim_in];
	    } else if(arondx>xim_in && arondy>=0){
	      fel[j+height_2][i+width_2]= im_in->fel[arondy][xim_in];
	    } else if(arondx>=0 && arondy<0){
	      fel[j+height_2][i+width_2]= im_in->fel[0][arondx];
	    } else if(arondx>=0 && arondy>=yim_in){
	      fel[j+height_2][i+width_2]= im_in->fel[yim_in][arondx];
	    } else if(arondx<0 && arondy>=0){
	      fel[j+height_2][i+width_2]= im_in->fel[arondy][0];
	    } else if(arondx>=xim_in && arondy>=0){
	      fel[j+height_2][i+width_2]= im_in->fel[arondy][xim_in];
	      }
	}
    }  
}

/****************************************************************/
void ImageContent::scale(DARY *im_in, float scalex, float scaley){
    float px, py, dx, dy;
    int arondx, arondy;
    int xim_in=im_in->x()-1;
    int yim_in=im_in->y()-1;
    
    for(uint j=0;j<y_size; j++){
	for(uint i=0;i<x_size; i++){
	  px = i*scalex; 
	  py = j*scaley;
	  arondx = (int) floor(px);
	  arondy = (int) floor(py);
	  dx = px -  arondx;
	  dy = py -  arondy;     
	  if(arondx<xim_in && arondy<yim_in){
	    fel[j][i]= (1.0 - dy)*((1.0 - dx)*im_in->fel[arondy][arondx] +
				  dx*im_in->fel[arondy][arondx+1]) +
	      dy*((1.0 - dx)*im_in->fel[arondy+1][arondx] +
		  dx *im_in->fel[arondy+1][arondx+1]);
	  } else if(arondx==xim_in && arondy<yim_in){
	    fel[j][i] = (1.0 - dy)*im_in->fel[arondy][arondx] +
	      dy*(im_in->fel[arondy+1][arondx]);	  	      
	  } else if(arondx<xim_in && arondy==yim_in){
	    fel[j][i]= (1.0 - dx)*im_in->fel[arondy][arondx] +
	      dx*im_in->fel[arondy][arondx+1];	      
	  }else if(arondx==xim_in && arondy==yim_in){
	    fel[j][i]= im_in->fel[arondy][arondx];
	  }else if(arondx>xim_in && arondy<=yim_in){fel[j][i]=im_in->fel[arondy][xim_in];
	  }else if(arondx<=xim_in && arondy>yim_in){fel[j][i]=im_in->fel[yim_in][arondx];
	  }else fel[j][i]=im_in->fel[yim_in][xim_in]; 
	}
    } 
}

void ImageContent::normalize(float min_in, float max_in){
  float sc=255.0/(max_in-min_in);
  if(buftype==FLOAT){
    for (uint i = 0; i < tsize; i++){
      if(fel[0][i]<min_in)fel[0][i]=min_in;
      else if(fel[0][i]>max_in)fel[0][i]=max_in;
      fel[0][i] = ((fel[0][i]-min_in)*sc);      
    }   
  }else if(buftype==UCHAR){
    for (uint col = 0; col < tsize; col++){
      if(bel[0][col]<min_in)bel[0][col]=(unsigned char)min_in;
      else if(bel[0][col]>max_in)bel[0][col]=(unsigned char)max_in;
      bel[0][col] = (unsigned char)((bel[0][col]-min_in)*sc);
    }    
  }     
}

void ImageContent::normalize(){

  float sc,max,min;
  if(buftype==FLOAT){
    max=fel[0][0];min=fel[0][0];
    for (uint col = 0; col < tsize; col++){
      if(max<fel[0][col])max=fel[0][col];
      else if(min>fel[0][col])min=fel[0][col];
    }
    sc=255.0/(max-min);
    for (uint i = 0; i < tsize; i++){
      fel[0][i] = ((fel[0][i]-min)*sc);      
    }   
  }else if(buftype==UCHAR){
    max=bel[0][0];min=bel[0][0];
    for (uint col = 0; col < tsize; col++){
      if(max<(float)bel[0][col])max=(float)bel[0][col];
      else if(min>(float)bel[0][col])min=(float)bel[0][col];
    }
    sc=255.0/(max-min);
    for (uint col = 0; col < tsize; col++){
      bel[0][col] = (unsigned char)((bel[0][col]-min)*sc);
    }    
  }     
}




void ImageContent::crop(DARY *img, int x, int y){
  int dx=x_size>>1;
  int dy=y_size>>1;
  int iy=y-dy;
  int ix=x-dx;
  uint jy=y+dy;
  uint jx=x+dx;
  int sx=(ix<0)?(-ix):0;
  int sy=(iy<0)?(-iy):0;
  int ex=(jx<img->x())?(x_size):(img->x()-ix);
  int ey=(jy<img->y())?(y_size):(img->y()-iy);
   
  if(buftype==FLOAT){
    for (int i = sy; i < ey; i++){
      for (int j = sx; j < ex; j++){
	fel[i][j]= img->fel[iy+i][ix+j];
      }   
    }
  }else if(buftype==UCHAR){
    for (int i = sy; i < ey; i++){
      for (int j = sx; j < ex; j++){
	bel[i][j]= img->bel[y+i][x+j];
      }   
    }    
  }  
   
}






/****************************************************************/
void ImageContent::float2char()
{
	if(buftype==FLOAT){
	  initUChar(y_size,x_size);
	  float max,min;
	  max=fel[0][0];min=fel[0][0];
	  for (uint col = 0; col < tsize; col++){
	    if(max<fel[0][col])max=fel[0][col];
	    else if(min>fel[0][col])min=fel[0][col];
	  }
	 
	  if(min<0 || max >255){
	    float sc=0;
	    if(max!=min)
	      sc=255.0/(max-min);
	    cout << " min " << min << " < 0 or max "<< max<< " > 255, sc=" << sc<< endl;
	    for (uint col = 0; col < tsize; col++){
	      bel[0][col] = (unsigned char)(sc*(fel[0][col]-min));
	    }    	    
	  }else {
	    for (uint col = 0; col < tsize; col++){
	      bel[0][col] = (unsigned char)(fel[0][col]);
	    }    	    
	  }	  	  
	  buftype=UCHARFLOAT;
	}
	if(buftype==UCHAR || buftype==CUCHAR || buftype==UCHARFLOAT || buftype==CUCHARFLOAT){
	}else cout << "wrong buffer type " << buftype << endl;
	
} 
 

 
/****************************************************************/
void ImageContent::toGRAY(void){
  if(buftype==CUCHAR){
    initUChar(y_size,x_size);
    for(uint i=0;i<tsize;i++){
      bel[0][i]=(unsigned char)((belr[0][i]+belg[0][i]+belb[0][i])/3.0);
    }
    delete [] belr[0];delete []  belr;belr=NULL;
    delete [] belg[0];delete []  belg;belg=NULL;
    delete [] belb[0];delete []  belb;belb=NULL;
    buftype=UCHAR;    
  }
}

/****************************************************************/
ImageContent::~ImageContent(void){
  delete []filename;
  if(buftype==UCHAR || buftype==UCHARFLOAT){    
    delete []  bel[0];delete []  bel;//buffer=NULL;
  }
  if(buftype==CUCHAR || buftype==CUCHARFLOAT){
    delete [] belr[0];delete []  belr;//rbuffer=NULL;
    delete [] belg[0];delete []  belg;//gbuffer=NULL;
    delete [] belb[0];delete []  belb;//bbuffer=NULL;
  }  
  if(buftype==FLOAT || buftype==UCHARFLOAT){
    delete [] fel[0];
    delete [] fel;//fel=NULL;
  }
  if(buftype==CFLOAT || buftype==CUCHARFLOAT){
    delete [] felr[0];
    delete [] felr;//el1=NULL;
    delete [] felg[0];
    delete [] felg;//fel2=NULL;
    delete [] felb[0];
    delete [] felb;//fel3=NULL;
  }
  buftype=0;
}

namespace kma {

  ImageContent *load_convert_gray_image(const char *image_filename) 
  {
    cout << "load_convert_gray_image, loading image from: " << image_filename << endl;
    assert(filesys::check_file(image_filename) && "file not found");

    ImageContent *pkmaimg = new ImageContent(image_filename);

    cout << "loaded image, width: " << pkmaimg->x() << ", height: " << pkmaimg->y() << ", type: " << pkmaimg->getType() << endl;

    pkmaimg->toGRAY();
    pkmaimg->char2float();
    return pkmaimg;
  }

}


kma::ImageContent *add_image_border2(kma::ImageContent *kmaimg, int b, int &corrected_b)
{
  assert(kmaimg != 0);
  assert(kmaimg->getType() == 2); /* imageContent.h - FLOAT */
  //  assert(b >= 0 && (unsigned int)b < kmaimg->x() && (unsigned int)b < kmaimg->y());
  assert(b >= 0);

  if (!((unsigned int)b < kmaimg->x() && (unsigned int)b < kmaimg->y())) {
    int new_b = std::min(kmaimg->x(), kmaimg->y()) - 1;
      
    cout << "add_image_border, warning: border bigger then the image" << endl;
    cout << "\treducing added border from " << b << " to " << new_b << endl;
    b = new_b;
  }


  kma::ImageContent *kmaimg2 = new kma::ImageContent(2*b + kmaimg->y(), 2*b + kmaimg->x());
  assert(kmaimg->fel != 0);
  assert(kmaimg2->fel != 0);

  int w = kmaimg->x();
  int h = kmaimg->y();

  /* copy image */
  for (int ix = 0; ix < w; ++ix)
    for (int iy = 0; iy < h; ++iy)
      kmaimg2->fel[b + iy][b + ix] = kmaimg->fel[iy][ix];


  //int bx1 = b+1;
  int bx2 = b+w;
  int by1 = b+1;
  int by2 = b+h;

  /* add border to the left and right */
  for (int bidx = 1; bidx <= b; ++bidx) {
    
    for (int yidx = by1; yidx <= by2; ++yidx) {
      kmaimg2->fel[yidx-1][bidx-1] = kmaimg->fel[yidx - by1][b - bidx];
      kmaimg2->fel[yidx-1][bx2+bidx-1] = kmaimg->fel[yidx - by1][w - bidx];
    }

    //I2(by1:by2, bidx) = I(:, b - bidx + 1);
    //I2(by1:by2, bx2+bidx) = I(:, w - bidx + 1);

  }

  /* add border on top and bottom */
  for (int bidx = 1; bidx <= b; ++bidx) {

    for (int xidx = 0; xidx < w + 2*b; ++xidx) {
      //kmaimg2->fel[bidx - 1][xidx] = kmaimg2->fel[by1 + b - bidx][xidx];
      kmaimg2->fel[bidx - 1][xidx] = kmaimg2->fel[by1 + b - bidx - 1][xidx];
      kmaimg2->fel[by2 + bidx - 1][xidx] = kmaimg2->fel[by2 - bidx][xidx];
    }

    //I2(bidx, :) = I2(by1 + b - bidx + 1, :);
    //I2(by2+bidx, :) = I2(by2 - bidx + 1, :);
  }

  corrected_b = b;
  return kmaimg2;
}

kma::ImageContent *add_image_border(kma::ImageContent *kmaimg, int b)
{
  int corrected_b;
  return add_image_border2(kmaimg, b, corrected_b);
}
