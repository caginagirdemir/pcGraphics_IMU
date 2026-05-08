function varargout = untitled(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end

function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;

guidata(hObject, handles);

if strcmp(get(hObject,'Visible'),'off')
    plot(1);
    grid on,axis([0 12 0 45]);
end

function varargout = untitled_OutputFcn(hObject, eventdata, handles)

varargout{1} = handles.output;


function pushbutton1_Callback(hObject, eventdata, handles)

axes(handles.axes1);
cla;






popup_sel_index = get(handles.popupmenu1, 'Value');

switch popup_sel_index
case 1
g = 9.81;       % yer cekimi ivmesi
t = 0:0.05:3;   % zaman
v_kutu = get(handles.edit1, 'String'); 
v_kutu = str2double(v_kutu);
y_ball = 0.5 * g * t.^2;    % topun konumu
y_ball = max(y_ball) - y_ball;  % topun konumu
x_ball = 10;    % 
y_kutu = 0;     %
x_kutu = v_kutu .* t;   % 
for i = 1: length(t)
    plot(x_ball, y_ball(i), 'o', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','g',...
                  'MarkerSize',10);
                   hold on;
              
    plot(x_kutu(i), y_kutu, 's', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','r',...
                  'MarkerSize',10);
                   hold off;
              
              
    grid on, axis([0 12 0 45]);
    pause(0.02)
end
    case 2
g = 24.8;       % yer cekimi ivmesi
t = 0:0.05:3;   % zaman
v_kutu = get(handles.edit1, 'String'); 
v_kutu = str2double(v_kutu);
y_ball = 0.5 * g * t.^2;    % topun konumu
y_ball = max(y_ball) - y_ball;  % topun konumu
x_ball = 10;    % 
y_kutu = 0;     %
x_kutu = v_kutu .* t;   % 
for i = 1: length(t)
    plot(x_ball, y_ball(i), 'o', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','g',...
                  'MarkerSize',10);
                   hold on;
              
    plot(x_kutu(i), y_kutu, 's', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','r',...
                  'MarkerSize',10);
                   hold off;
              
              
    grid on, axis([0 12 0 120]);
    pause(0.02)
end

    case 3
g = 1.624;       % yer cekimi ivmesi
t = 0:0.05:3;   % zaman
v_kutu = get(handles.edit1, 'String'); 
v_kutu = str2double(v_kutu);
y_ball = 0.5 * g * t.^2;    % topun konumu
y_ball = max(y_ball) - y_ball;  % topun konumu
x_ball = 10;    % 
y_kutu = 0;     %
x_kutu = v_kutu .* t;   % 
for i = 1: length(t)
    plot(x_ball, y_ball(i), 'o', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','g',...
                  'MarkerSize',10);
                   hold on;
              
    plot(x_kutu(i), y_kutu, 's', ... 
                  'LineWidth',2,...
                  'MarkerEdgeColor','k',...
                  'MarkerFaceColor','r',...
                  'MarkerSize',10);
                   hold off;
              
              
    grid on, axis([0 12 0 7.5]);
    pause(0.02)
end
end


% --------------------------------------------------------------------
function FileMenu_Callback(hObject, eventdata, handles)



% --------------------------------------------------------------------
function OpenMenuItem_Callback(hObject, eventdata, handles)

file = uigetfile('*.fig');
if ~isequal(file, 0)
    open(file);
end

% --------------------------------------------------------------------
function PrintMenuItem_Callback(hObject, eventdata, handles)

printdlg(handles.figure1)

% --------------------------------------------------------------------
function CloseMenuItem_Callback(hObject, eventdata, handles)

selection = questdlg(['Close ' get(handles.figure1,'Name') '?'],...
                     ['Close ' get(handles.figure1,'Name') '...'],...
                     'Yes','No','Yes');
if strcmp(selection,'No')
    return;
end

delete(handles.figure1)


function popupmenu1_Callback(hObject, eventdata, handles)

function popupmenu1_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
     set(hObject,'BackgroundColor','white');
end

set(hObject, 'String', {'Dunya', 'Jupiter', 'Ay'});



function edit1_Callback(hObject, eventdata, handles)

function edit1_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
