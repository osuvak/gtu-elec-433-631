classdef fft_coefs_manipulator < handle
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
 
 Updates (Onder Suvak):
   Commented through the whole code
     Thu May  7 00:48:14 AST 2020
%}

% Questions:
%   What is the syntax for class inheritance in Matlab/Octave?
%   What if this class were not a subclass of handle? How would
%     you modify the code composing the class (I would not even
%     want to work on this one!)?

    properties(SetAccess=private, GetAccess=public)
        x_t_original % original input in discrete time domain
        x_t          % signal in disc. time  domain
        x_f          % signal in disc. freq. domain
        
        K            % equal to (N-1) / 2
        N            % number of samples in signal (assumed odd)

        indices_t    % index range in disc. time  domain
        indices_f    % index range in disc. freq. domain
        
        w_o = 1      % angular frequency in rad/s

        % Questions:
        %   Is "logical" a class/type in Matlab/Octave?
        %     What if we had only "1" or "0" for the flag below?
        %   How do we define default values for the properties
        %     in a class?
        flag_real          = logical(1) 
            % flag on the signal having real (not complex) samples
            % default value "true  = logical(1)"
        flag_plot_maximize = logical(0)
            % flag for plot maximization or not
            % default value "false = logical(0)"
        
        plot_type = 'stem' % Can use 'stem' or 'plot'
    end % properties

    % Questions:
    %   Why do you think I would like to have multiple
    %     methods blocks in my class definition?
    %   Can I have multiple properties blocks as well?
    
    % ctor dtor
    methods(Access=public)
    
        function obj = fft_coefs_manipulator(x_t, varargin)
            % NOTE: Keep the original.
            obj.x_t_original = x_t;
            % NOTE: Store the signal in disc. time domain.
            obj.x_t = x_t;
            % Questions:
            %   Is there an assumption taken for granted
            %     while writing down the following?
            obj.N   = size(x_t, 2);
            
            % NOTE:
            %   This is the usual syntax for dealing with
            %     the optional arguments given through
            %     varargin.
            % Questions:
            %   I do not like the (2, 1) and (3, 2) tuples
            %     utilized in the part of the code below.
            %     I think it is error-prone. How would you
            %     improve this style?
            if nargin >= 2;
                % TODO: 
                %   I need to check if varargin{1} can be
                %   utilized as a flag in here.
                obj.flag_real = varargin{1};
            end
            
            if nargin >= 3;
                obj.w_o = varargin{2};
            end
            
            % TODO: 
            %   I need to check if N is odd in here.
            % Questions:
            %   Why would be better to return an error or throw
            %     an exception in a constructor, if the constructor
            %     receives inappropriate arguments, than to live with
            %     a zombie class instance?
            %   What is a zombie class instance by the way?
            obj.K = (obj.N - 1) / 2;
            
            % NOTE:
            %   "K" comes in handy for expressions similar to below.
            obj.indices_t = 0:(-1+obj.N);
            obj.indices_f = -obj.K:+obj.K;
        
            % NOTE:
            %   The two signals "x_t" in the disc. time and "x_f"
            %     in the disc. freq. domains is an inseparable pair.
            %     If one is modified, the other should be updated.
            % Questions:
            %   Is it possible to call a function in Matlab/Octave
            %     without the encapsulating parentheses "()" if you
            %     do not need to send any arguments to the function?
            obj.to_freq();
        end % function
    end % methods
    
    % utilities
    methods(Access=public)
        function set_w_o(obj, w_o)
            % NOTE:
            %   necessary if I would like to modify the angular
            %     freq. value
            obj.w_o = w_o;
        end
        
        function revert_to_original(obj)
            % NOTE:
            %   I may optionally want to revert to the original
            %     signal.
            obj.x_t = obj.x_t_original;
            obj.to_freq();
        end
    end % methods
    
    % operations (usually carried out in disc. freq. domain)
    methods(Access=public)
        function compute_derivative_in_time(obj)
            % Questions:
            %   Explain how the computation below works for
            %     computing the derivative in time through an
            %     operation carried out in the disc. freq. domain.
            obj.x_f = ...
                ( 1j * obj.w_o * [-obj.K:+obj.K] ) ...
                .* obj.x_f;
            % Questions:
            %   Why do I have this member function call over here?
            obj.to_time();
        end % function
    end % methods
        
    % plotting related
    methods(Access=public)
        function change_plot_type(obj, type_str)
            % TODO: 
            %   I need checks in here.
            % Questions:
            %   How do I check that a variable is of type string
            %     in Matlab/Octave?
            obj.plot_type = type_str;
        end
        
        function set_flag_plot_maximize(obj, lval)
            % NOTE:
            %   Plot maximization is buggy in Octave. That is
            %     why I rendered it optional through a flag.
            obj.flag_plot_maximize = lval;
        end
        
        function plot_freq(obj, varargin)
            % Questions:
            %   How does the piece of code below work in determining
            %     the string specifier for the title of the plot?
            title_str = 'Signal in Frequency Domain';
            if nargin >= 2
                title_str = varargin{1};
            end
            
            figure;
            % Questions:
            %   How else can we express the subplot(...) function
            %     call below?
            subplot(211)
            % Questions:
            %   What does the function lower(...) do below?
            %   Do we have also a function called upper(...)?
            %   Can we have strings as case identifiers in a
            %     switch statement? What about in C++?
            switch lower(obj.plot_type)
                case 'stem'
                    % Questions:
                    %   How can we define exotic colors through
                    %     their RGB specifiers in Matlab/Octave?
                    %   What do the identifiers 'LineWidth',
                    %     'Color', 'MarkerSize', 'MarkerEdgeColor'
                    %     'MarkerFaceColor' mean? Do we have more
                    %     of them that can be used in here?
                    stem( ...
                        obj.indices_f, real(obj.x_f), ...
                        'LineWidth', 3, 'Color', 'b', ...
                        'MarkerSize', 10, 'MarkerEdgeColor', 'k', ...
                        'MarkerFaceColor', 'r')
                    
                case 'plot'
                    plot( ...
                        obj.indices_f, real(obj.x_f), ...
                        'LineWidth', 3, 'Color', 'b')
                    
                otherwise
                    % TODO:
                    %   Generate an error or throw an exception.
                    % Questions:
                    %   How do I generate a meaningful error or
                    %     throw an exception in the current context?
            end
            % Questions:
            %   How is "sprintf" in Matlab/Octave different compared
            %     to that in C?
            title(sprintf('%s (Real Parts)', title_str))
            ylabel('Real Parts')
            
            % NOTE:
            %   For the second subplot the tasks are very similar
            %     to those in the first.
            subplot(212)
            switch lower(obj.plot_type)
                case 'stem'
                    stem( ...
                        obj.indices_f, imag(obj.x_f), ...
                        'LineWidth', 3, 'Color', 'b', ...
                        'MarkerSize', 10, 'MarkerEdgeColor', 'k', ...
                        'MarkerFaceColor', 'r')
                    
                case 'plot'
                    plot( ...
                        obj.indices_f, imag(obj.x_f), ...
                        'LineWidth', 3, 'Color', 'b')
                    
                otherwise
                    % TODO:
                    %   Generate an error or throw an exception.
            end
            title(sprintf('%s (Imag Parts)', title_str))
            ylabel('Imag Parts')
            xlabel('Discrete Frequency Indices')
            
            % Questions:
            %   My commment stands as to the codes for the two
            %     subplots being very similar to each other. Can
            %     you somehow render the code more concise?
            %   What would be the disadvantages of making the
            %     codes for the subplots more concise/brief in
            %     terms of maintainability?
            
            % NOTE:
            %   The following is how the plot can be optionally
            %     maximized.
            % Questions:
            %   What does the gcf() function do? Is there an
            %     alternative way to get hold of the relevant
            %     handle?
            if obj.flag_plot_maximize
                set( gcf(), 'units', 'normalized', ...
                     'position', [0 0 1 1] )
            end
        end % function
        
        function plot_time(obj, varargin)
            % NOTE:
            %   The "plot_time" member function has the same
            %     same structure as "plot_freq". In its current
            %     form no additional comments necessary.
            title_str = 'Signal in Time Domain';
            if nargin >= 2
                title_str = varargin{1};
            end
            
            figure;
            switch lower(obj.plot_type)
                case 'stem'
                    stem( ...
                        obj.indices_t, obj.x_t, ...
                        'LineWidth', 3, 'Color', 'b', ...
                        'MarkerSize', 10, 'MarkerEdgeColor', 'k', ...
                        'MarkerFaceColor', 'r')
                    
                case 'plot'
                    plot( ...
                        obj.indices_t, obj.x_t, ...
                        'LineWidth', 3, 'Color', 'b')
                    
                otherwise
                    % TODO:
                    %   Generate an error or throw an exception.
            end
            title(title_str)
            xlabel('Discrete Time Indices')
            ylabel('Signal')
            
            if obj.flag_plot_maximize
                set( gcf(), 'units', 'normalized', ...
                     'position', [0 0 1 1] )
            end
        end % function
    end % methods
    
    % core
    methods(Access=public)
    
        % Could be a private member function.
        function to_freq(obj)
            % NOTE:
            %   This is an almost generic function for the
            %   transformation from the discrete time domain
            %   to the discrete frequency domain. I make
            %   explicit use of the signals having an odd
            %   number of samples.
            
            % Questions:
            %   What is done in the following line except the
            %     fft transformation?
            obj.x_f = fft(obj.x_t) / obj.N;
            % Questions:
            %   Explain the details of the fftshift operation
            %     in the next line of code, valid for an odd
            %     number of samples.
            obj.x_f = [ obj.x_f(:, (2+obj.K):obj.N) , ...
                        obj.x_f(:, 1:(1+obj.K)) ];
        end % function
        
        % Could be a private member function.
        function to_time(obj)
            % Questions:
            %   Could the following operations for the inverse
            %     fft transformation be carried out in a single
            %     line of code? 
            %   Would a permutation of the operations thus carried
            %     out also be possible? In other words, is it
            %     possible to carry out the following operations
            %     in a different order than the one shown?
            obj.x_t = obj.x_f * obj.N;
            obj.x_t = [ obj.x_t(:, (1+obj.K):obj.N) , ...
                        obj.x_t(:, 1:obj.K) ];
            obj.x_t = ifft( obj.x_t );
            
            % Questions:
            %   This is a crucial question. If we are dealing
            %     with only real signals in the discrete time
            %     domain, and if the operations carried out will
            %     keep the representation in the discrete time
            %     domain for real (if we are sure of this latter aspect),
            %     then why would we need the following operation?
            %     Note that the check with the available flag
            %     is only a matter of flexibility I desired to
            %     have the whole code possess.
            if obj.flag_real
                obj.x_t = real(obj.x_t);
            end
        end % function
        
    end % methods
    
end % classdef