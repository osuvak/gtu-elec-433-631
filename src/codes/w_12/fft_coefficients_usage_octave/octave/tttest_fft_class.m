%{
/*
 * This file is part of the "dev-in-place" repository located at:
 * https://github.com/osuvak/dev-in-place
 * 
 * Copyright (C) 2020  Onder Suvak
 * 
 * For licensing information check the above url.
 * Please do not remove this header.
 * */
 
 Updates to the code
   Commented through with interspersed questions on
     Thu May  7 12:45:17 AST 2020
%}

% Questions:
%   Why do we close all figures before clearing anything,
%     especially classes?
%   What do all these clear statements do? What are the
%     differences between them?
close all;
clear variables;
clear classes;

% Notes:
%   This is a simple mechanism for coding tests. Makes use
%     of a switch case statement. And we comment out all but
%     one of the choices (case identifiers) so that the indicated
%     test can be run.
% Questions:
%   As much as I like switch-case statements and would like to
%     exploit them to their full extent, I think in the present
%     case it would be much better if I were to invoke the chosen
%     test through its identifier stored in a (key, lambda) pair
%     in a hash or dictionary as in python. The lambdas would each
%     call a certain function declared in the same python script
%     as the current one. Can you discern why I am not easily
%     able to resort to this preferred style in Matlab/Octave?

ch = 'sine_cosine';
%  ch = 'step_function';
%  ch = 'triangular';

switch lower(ch)
    case 'sine_cosine'
        % Note: N is odd.
        N = 21;
        % Note: T is meant to denote the period.
        T = 1e-3;
        % Questions:
        %   What does the command "linspace(...)" do?
        %   Why am I generating "1+N" points through
        %     "linspace(...)" and not "N"?
        t = linspace(0, T, 1+N);
        % Note: Generate and stack discrete time signals.
        x = [ sin(2*pi/T*t) ; cos(2*pi/T*t) ];
        % Q: What does the following piece of code do?
        % Q: Is there an alternative way of doing the same thing?
        x(:, end) = [];
        
        % Note: 
        %   "results" is declared and initialized as an
        %     empty cell array.  
        results = {};
        for kk = 1:size(x, 1)
            % Questions:
            %   This part is really important. How do you append
            %     new items at the end of a cell array? 
            %   "fft_coefs_manipulator(...)" is a constructor call
            %     for the class with the same name. However,
            %     the definition for this class does not reside in
            %     this script. Where is it? In another .m file.
            %     Do I import this other .m file? No. Then, how
            %     come am I able to call the ctor? What does the
            %     ctor return? How am I able to store this in
            %     a cell array as an item? Also, does the fact that
            %     the class "fft_coefs_manipulator" has been
            %     subclassed from "handle" help any in such an
            %     assignment and the following operations?
            results{end+1} = fft_coefs_manipulator(x(kk, :));
            %  Note:
            %    The following are used to set internal variables
            %      within the recently created class instance so
            %      that the plots obtained when we need them
            %      will appear as we would like them to.
            results{end}.set_flag_plot_maximize(logical(0));
%              results{end}.change_plot_type('plot');
        end
        
        for kk = 1:size(results, 2)
            % Note:
            %   If we do not want to use the default title,
            %     then a customized one has to be sent to the
            %     plot function(s). This feature as you know
            %     has been made optional through the varargin
            %     variable.
            title_str = sprintf('Signal %d in Time Domain', kk);
            results{kk}.plot_time(title_str);
%              results{kk}.plot_time();

            results{kk}.plot_freq();
        end
    
    case 'step_function'
        N = 21;
        ratio = 0.3;
        
        % Note:
        %   This is how we can simply generate a pulse signal
        %     with an adjusted duty cycle.
        % Questions:
        %   Perhaps you would like to experiment with different
        %     duty cycle values, or write a piece of code to
        %     loop through a range of duty cycles. See what
        %     happens.
        x = zeros(1, N);
        x(1:ceil(ratio*N)) = 1;
        
        results = {};
        results{end+1} = fft_coefs_manipulator(x);
        results{end}.plot_time();
        results{end}.plot_freq();
    
    case 'triangular'
        N = 101;
        
        % Questions:
        %   This is not a perfect triangular function, certainly
        %     not the one I intended to define initially. Tell
        %     me why.
        K = (N-1) / 2;
        x = zeros(1, N);
        x(1:(1+K)) = ( [1:(1+K)] - 1 ) / (K);
        x((2+K):N) = x(K:-1:1);
        
        results = {};
        results{end+1} = fft_coefs_manipulator(x);
        results{end}.change_plot_type('plot');
        results{end}.plot_time();
        results{end}.plot_freq();
        
        % Questions:
        %   Does the assignment below result in class instances
        %     being copied? Tell me why or why not.
        oa = results{end};
        % Questions:
        %   When you compute the derivative in time, the resulting
        %     signal is not going to be a perfect pulse. Look up
        %     the Gibbs phenomenon.
        oa.compute_derivative_in_time();
        oa.plot_time();
        oa.plot_freq();
        
        % Note: Recall that I added a feature to revert to the
        %       original signal.
        oa.revert_to_original();
        oa.plot_time();
        oa.plot_freq();
        
    otherwise
        disp('No such test.')
        
end % switch