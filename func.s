section .text
global drawPolynomialAsm



drawPolynomialAsm:
	push rbp
	mov rbp, rsp

	
  movss DWORD [rbp-48], xmm0  ; imgWidth
  movss DWORD [rbp-52], xmm1  ; imgHeight
  movss DWORD [rbp-56], xmm2  ; parametr a
  movss DWORD [rbp-60], xmm3  ; parametr b
  movss DWORD [rbp-64], xmm4  ; parametr c
  movss DWORD [rbp-68], xmm5  ; parametr d
  movss DWORD [rbp-72], xmm6  ; Jump S
  mov QWORD [rbp-80], rdi  ; pixels tabl

  pxor xmm7,xmm7
  movss DWORD [rbp-4], xmm7	; float x = 0
  movss DWORD[rbp-8],xmm5 ; float y=d
  mov DWORD[rbp-12],0 ; int i=0
    

  mov DWORD[rbp-32],0x3F800000 ;1
  mov DWORD[rbp-36],0x40000000 ;2
  mov DWORD[rbp-40],0x40400000 ;3
  mov DWORD[rbp-44],0x42c80000 ;100
  ;movss xmm4,DWORD[rbp-60];c
  ;mulss xmm4,xmm4 ;c*c
  ;addss xmm4,DWORD[rbp-32] ;c*c+1
  ;divss xmm6,xmm4 ;dx2=S/(c*c+1)

  ;cvtss2sd xmm6,xmm6
  ;sqrtsd xmm6,xmm6 ;dx=sqrt(sdx2)
  ;cvtsd2ss xmm6,xmm6
  ;movss DWORD[rbp-20],xmm6 ; dx=sqrt(sdx2)


  mulss xmm5,xmm1; int j=y*imgHeight
  
;  div xmm4,0x41200000;imgHeight/10
  divss xmm5,DWORD[rbp-44]
  movss DWORD[rbp-16],xmm5 ; int j=(y*imgHeight)/(imgHeight/10)

    
  ;movss  xmm4,DWORD[rbp-60]  ; parametr c
  ;mulss xmm4,xmm6;dy=c*dx
  ;movss DWORD[rbp-24],xmm4;dy
    ;movss DWORD [rbp-4], xmm6 ;x=dx	
    
  ;movss xmm3,xmm1 ; imgHeight
  ;subss xmm3,xmm5
  ;mulss xmm3,xmm0 ; *imgWidth
  ;subss xmm3,DWORD[rbp-32]
  ;cvttss2si eax,xmm3
  ;mov DWORD[rbp-28],eax ; index=(imgHeight-j)*imgWidth
mainLoop:

  movss xmm3,DWORD[rbp-4];x
  mulss xmm3,xmm0;i=x*imgWidth
  divss xmm3,DWORD[rbp-44];/100
  
  cvttss2si eax,xmm3
  cvtsi2ss xmm3,eax
  movss DWORD[rbp-12],xmm3;i=x*imgWeight/100

  movss xmm4,DWORD[rbp-8];y
  mulss xmm4,xmm1;j=y*imgHeight
  divss xmm4,DWORD[rbp-44];/100
  cvttss2si eax,xmm4
  cvtsi2ss xmm4,eax
  movss DWORD[rbp-16],xmm4;j

  movss xmm2,xmm1 ;imgHeight
  subss xmm2,DWORD[rbp-16] ; -j
  mulss xmm2,xmm0 ;*imgWidth

  movss xmm7,xmm0 ; imgWidth
  subss xmm7,DWORD[rbp-12] ; -i

  subss xmm2,xmm7; index
  ;subss xmm2,DWORD[rbp-32];-1
  cvttss2si eax,xmm2
  mov DWORD[rbp-28],eax; index

  movss xmm7,DWORD[rbp-40] ;3
  mulss xmm7,DWORD[rbp-4];*x
  mulss xmm7,DWORD[rbp-4];*x
  mulss xmm7,DWORD[rbp-56];*a

  movss xmm6,DWORD[rbp-36] ;2
  mulss xmm6,DWORD[rbp-4];*x
  mulss xmm6,DWORD[rbp-60];*b

  addss xmm7,xmm6 ;3*x*x*a+2*x*b
  addss xmm7,DWORD[rbp-64] ;+c

  movss xmm5,xmm7 ;copy xmm7
  mulss xmm7,xmm5 ;^2
  addss xmm7,DWORD[rbp-32];+1

  movss xmm6,DWORD[rbp-72]; S
  mulss xmm6,xmm6 ;S*S
  divss xmm6,xmm7 ;dx2
  cvtss2sd xmm6,xmm6 
  sqrtsd xmm6,xmm6 ;dx=sqrt(sdx2)
  cvtsd2ss xmm6,xmm6
  movss DWORD[rbp-20],xmm6

  mulss xmm5,xmm6; dy=(3*x*x*a+2*x*b+c)*dx
  movss DWORD[rbp-24],xmm5

  movss xmm2,DWORD[rbp-4];x
  addss xmm2,xmm6;x+=dx
  movss DWORD[rbp-4],xmm2

  movss xmm2,DWORD[rbp-8];y
  addss xmm2,xmm5;y+=dy
  movss DWORD[rbp-8],xmm2



  movss xmm0,DWORD[rbp-48]
  movss xmm3,DWORD[rbp-12]
  ucomiss xmm3,xmm0
  ja end
  movss xmm4,DWORD[rbp-16]
  movss xmm1,DWORD[rbp-52]
  ucomiss xmm4,xmm1
  ja end


  ;pixels[index]=0
  mov eax,DWORD[rbp-28]
  cdqe
  lea rdx,[0+rax*4]
  mov rax,QWORD[rbp-80]
  add rax,rdx
  mov DWORD[rax],0x00000000 ; mark black point





  jmp mainLoop


end:
    pop rbp
    ret
