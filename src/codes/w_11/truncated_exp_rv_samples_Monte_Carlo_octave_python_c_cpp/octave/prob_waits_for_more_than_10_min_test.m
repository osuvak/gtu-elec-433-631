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
 
 Updates
   Commented through with interspersed questions on
     Wed Jun 10 16:35:24 AST 2020
%}

% Q:
%   Is there a particular reason why the "close" and "clear"
%     statements below are stated in the order given?
close all
clear variable
clear classes

% Q:
%   What is a Monte Carlo type of analysis, and what is it used
%     for?
%   What do I mean by a frequency count when approximating
%     a probability value through a Monte Carlo analysis?
%   What is an ensemble in Monte Carlo analyses?

no_mc = 100000;  % no of samples in ensemble
lam   = 1. / 10; % lambda for the exp. dist. rv
time_to_wait = ... % minimum no of minutes to wait
    10.;
total_min_in_hour = ... % total no of minutes in an hour
    60.;
  
% Q:
%   How will each entry in "arrival_times" be distributed?
arrival_times = ...
    total_min_in_hour * rand(1, no_mc);
% Q:
%   Explain why "result" is the variable over which the
%     stated and relevant frequency count operation will
%     be carried out.
result = ...
    zeros(1, no_mc);

% Q:
%   Recall what the numel() function does.
%   How are the iterates in this for loop indexed?
for kk = 1:numel(arrival_times)
    % Q:
    %   What does "continue" do?
    %   Could the following "if else" control flow statement
    %     be constructed without resorting to "continue"?
    if arrival_times(kk) > total_min_in_hour - time_to_wait
        % Q:
        %   Why do we choose not to deal with this case (examining
        %     the logical value check for this "if" statement)?
        %     Notice that this is a problem-specific question.
        continue;
    else
        % Q:
        %   Would the code below work correctly with 
        %     flag_valid_sample set initially to 0 (zero)?
        %   What does logical() signify? Is it a function call
        %     or something else?
        %   Is there a chance for "sample" to continue having
        %     the assigned value "[]" at the end of the "else"
        %     statement?
        %   What does "[]" mean in Matlab/Octave?
        %   Will the two variables continue to remain in scope
        %     when we are done with this "else" part of the
        %     "if else" control flow statement?
        flag_valid_sample = logical(0);
        sample = [];
        % Q:
        %   Could the while loop below continue to run through
        %     iterations indefinitely, is there such a possibility?
        % Q:
        %   If your answer is yes to the previous question, then
        %     how can we expect the while loop below to be finalized
        %     in a finite amount of time? What is the answer to this
        %     question founded upon?
        while ~flag_valid_sample
            % Q:
            %   How is the inverse transform method utilized
            %     for the generation of a sample "x" obeying
            %     the exponential distribution with parameter
            %     lambda ("lam" in the code)?
            u = rand();
            x = - 1. / lam * log(1. - u);
            % Q:
            %   Is it the sample of an exponentially distributed
            %     random variable that we need when "x" has to be
            %     generated? If no, then what do we need?
            %   Explain how the "if" control flow statement below
            %     implements the rejection method necessary to
            %     generate samples of a random variable belonging to
            %     a truncated distribution.
            %   Is it below that there happens to be a statement
            %     that is able to terminate the enclosing "while"
            %     loop?
            if arrival_times(kk) + x < total_min_in_hour
                flag_valid_sample = logical(1);
                sample = x;
            end
        end
        % Q:
        %   "result" is our record-keeping variable for a frequency
        %     count. We have a conditional entry setting with
        %     assignment to 1. What does this signify? What would
        %     assignment to 0 signify and why do we not have it
        %     explicitly coded below?
        if sample > time_to_wait
            result(kk) = 1.;
        end
    end
end

% Q:
%   This is where the frequency count operation through the record-
%     keeper "result" is done. Comment what would happen if we chose
%     have a "result" variable with many more entries.
%   Why cannot the operation below yield a value greater than 1 or
%     smaller than 0?
%   Why is the operation below yield an approximation for the
%     requested probability?
disp( 'Probability of Waiting for more than 10 min:' );
disp( sprintf( '  %.6f', sum(result) / numel(result) ) );