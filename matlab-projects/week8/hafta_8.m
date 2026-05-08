clear all
clc
m1=1; %kütle
r1=1; %yaricap
X1=[3,3]; %ilk pozisyon
V1=[0.1,0.0]; %ilk hiz
m2=2; %kütle
r2=1; %yaricap
X2=[10,4]; %ilk pozisyon
V2=[-0.1,0]; %ilk hiz
patch([0,0,14,14],[0,10,10,0],'g','FaceAlpha',0.7);
grid on;
axis square equal;
hold on;
a=[0:0.1:2*pi]; %daire noktalari 0.1 hassasiyet
Xcircle=cos(a); 
Ycircle=sin(a);
ball1=patch (X1(1)+r1*Xcircle, X1(2)+r1*Ycircle,'r','FaceAlpha',1);
ball2=patch (X2(1)+r2*Xcircle, X2(2)+r2*Ycircle,'b','FaceAlpha',1);


for i=1:5000
    
    X1=X1+V1; %konuma hiz eklenerek yeni konum elde edilmesi
    X2=X2+V2;   %konuma hiz eklenerek yeni konum elde edilmesi
    
    %top 1 in border çarp??ma kontrolü
    if (X1(1)<=r1)
        X1(1)=r1;
        V1(1)=-V1(1);
    end
    if(X1(1)>=14-r1)
        X1(1)=14-r1;
        V1(1)=-V1(1);
    end    
    if (X1(2)<=r1)
        X1(2)=r1;
        V1(2)=-V1(2);
    end
    if (X1(2)>=10-r1)
        X1(2)=10-r1;
        V1(2)=-V1(2);
    end
    
    %top 2 in border çarp??ma kontrolü
    if (X2(1)<=r2)
        X2(1)=r2;
        V2(1)=-V2(1);
    end
    if (X2(1)>=14-r2)
        X2(1)=14-r2;
        V2(1)=-V2(1);
    end    
    if (X2(2)<=r2)
        X2(2)=r2;
        V2(2)=-V2(2);
    end
    if (X2(2)>=10-r2)
        X2(2)=10-r2;
        V2(2)=-V2(2);
    end
    
    if (norm (X1-X2)<=r1+r2) %carpisma kontrolü
    
    u1=V1; %carpisma öncesi hiz u1 de?iskenine
    u2=V2;  %carpisma öncesi hiz u2 de?iskenine
    
    %vektör normallerini hesaplama
    u12=norm(u1)*cos(atan2(u1(2),u1(1))-atan2(X2(2)-X1(2),X2(1)-X1(1)));
    u11=norm(u1)*sin(atan2(u1(2),u1(1))-atan2(X2(2)-X1(2),X2(1)-X1(1)));
    u21=norm(u2)*cos(atan2(u2(2),u2(1))-atan2(X1(2)-X2(2) , X1(1)-X2(1)));
    u22=norm(u2)*sin(atan2(u2(2),u2(1))-atan2(X1(2)-X2(2) , X1(1)-X2(1)));
    v12 = ( (m1-m2)*u12 - 2*m2*u21 ) / (m1+m2); 
    v21 = ( (m1-m2)*u21 + 2*m1*u12 ) / (m1+m2);
    
    %capisma sonrasi hiz vektörü hesaplama
    V1=u11*[-sin(atan2(X2(2)-X1(2) , X2(1)-X1(1))),cos(atan2(X2(2)-X1(2) , X2(1)-X1(1)))] + v12*[cos(atan2(X2(2)-X1(2) , X2(1)-X1(1))),sin(atan2(X2(2)-X1(2) , X2(1)-X1(1)))];
    V2=u22*[-sin(atan2(X1(2)-X2(2) , X1(1)-X2(1) )),cos(atan2(X1(2)-X2(2) , X1(1)-X2(1) ))] - v21*[cos(atan2(X1(2)-X2(2) , X1(1)-X2(1) )),sin(atan2(X1(2)-X2(2) , X1(1)-X2(1) ))];
    
end %if, carpisma kontrolü

%ekrana plot ettirme
    set(ball1,'XData',X1(1)+r1*Xcircle, 'YData', X1(2)+r1*Ycircle);
    set(ball2,'XData',X2(1)+r2*Xcircle, 'YData', X2(2)+r2*Ycircle);
    drawnow;

end %for döngüsü