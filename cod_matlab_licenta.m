% Deschideți portul serial COM3
s = serial('COM3');
set(s, 'BaudRate', 9600); % Setează viteza de comunicație la 9600 baud
fopen(s); % Deschide portul serial

% Inițializarea figurii și a graficului
figure;
hPlot = plot(0, 0, 'o-'); % Inițializăm un grafic gol cu un punct
xlabel('Măsurători');
ylabel('Date');
title('Graficul datelor de pe COM3');
grid on;

% Setăm limitele axei Y
ylim([10 45]); % Setează limitele pentru axa y

% Numărul maxim de date pe grafic
maxDataPoints = 30;

% Initializăm vectorii pentru înregistrarea datelor
data = zeros(1, maxDataPoints);
timestamps = zeros(1, maxDataPoints);

% Variabila pentru contorul de date
count = 1;

% Bucla pentru citirea și actualizarea datelor în timp real
while ishandle(hPlot) % Continuă bucla până când fereastra graficului este închisă
    % Citirea datelor de pe portul serial
    newData = str2double(fgetl(s)); % Conversie la număr real
    
    % Actualizarea vectorilor de date
    data = [data(2:end), newData]; % Actualizăm vectorul de date cu un nou punct
    timestamps = 1:numel(data); % Actualizăm vectorul de timestamp-uri
    
    % Actualizarea graficului
    set(hPlot, 'XData', timestamps, 'YData', data);
    
    % Pauză mică între citiri pentru a nu supraîncărca procesorul
    pause(0.1);
end

% Închideți portul serial la încheierea buclei
fclose(s);
