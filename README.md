# arc-02-my_ls
<div class="card-block">
<div class="row">
<div class="col tab-content">
<div class="tab-pane active show" id="subject" role="tabpanel">
<div class="row">
<div class="col-md-12 col-xl-12">
<div class="markdown-body">
<p class="text-muted m-b-15">
</p><h1>My Ls</h1>
<p>Remember to git add &amp;&amp; git commit &amp;&amp; git push each exercise!</p>
<p>We will execute your function with our test(s), please DO NOT PROVIDE ANY TEST(S) in your file</p>
<p>For each exercise, you will have to create a folder and in this folder, you will have additional files that contain your work. Folder names are provided at the beginning of each exercise under <code>submit directory</code> and specific file names for each exercise are also provided at the beginning of each exercise under <code>submit file(s)</code>.</p>
<hr>
<table>
<thead>
<tr>
<th>My Ls</th>
<th></th>
</tr>
</thead>
<tbody>
<tr>
<td>Submit directory</td>
<td>.</td>
</tr>
<tr>
<td>Submit files</td>
<td>Makefile - *.c - *.h</td>
</tr>
</tbody>
</table>
<h3>Description</h3>
<h3>SPECIFICATIONS</h3>
<p>Write a programm called <code>my_ls</code>. Following the specifications of this man page.</p>
<h3>NAME</h3>
<p>my_ls -- list directory contents</p>
<h3>SYNOPSIS</h3>
<p>my_ls [-at] [file ...]</p>
<h3>DESCRIPTION</h3>
<p>For each operand that names a <em>file</em> of a type other than directory, <strong>my_ls</strong> displays its name as well as any requested, associated information. For each operand that names a <em>file</em> of type directory, <em>my_ls</em> displays the names of files contained within that directory, as well as any requested, associated information.</p>
<p>If no operands are given, the contents of the current directory are displayed. If more than one operand is given, non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexicographical order.</p>
<p>The following options are available:</p>
<ul>
<li>
<strong>-a</strong> Include directory entries whose names begin with a dot (.).</li>
<li>
<strong>-t</strong> Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.</li>
</ul>
<h3>Requirements</h3>
<ul>
<li>Your code must be compiled with the flags <strong>-Wall -Wextra -Werror</strong>.</li>
</ul>
<h3>Hint(s)</h3>
<ul>
<li>Watch out for <strong>memory leaks</strong> !</li>
<li>You can test your code against memory errors by compiling with the debugging flags <strong>-g3 -fsanitize=address</strong>
</li>
<li><strong>Global variables are strictly FORBIDDEN</strong></li>
<li>tv_sec AND tv_nsec are used for the -t options ;-)</li>
<li>
<code>st_mtime</code> is not what you want to use. You want to use <code>st_mtim</code>
</li>
</ul>
<h3>Technical information</h3>
<ol>
<li>you must create a Makefile, and the ouput is the command itself</li>
<li>You can use:</li>
</ol>
<ul>
<li>malloc(3)</li>
<li>free(3)</li>
<li>printf(3)</li>
<li>write(2)</li>
<li>stat(2)</li>
<li>lstat(2)</li>
<li>opendir(2)</li>
<li>closedir(2)</li>
<li>readdir(2)</li>
</ul>
<ol start="3">
<li>You can NOT use:</li>
</ol>
<ul>
<li>Any functions / syscalls which does not appear in the previous list</li>
<li>Yes, it includes <strong>exit</strong>
</li>
<li>Multiline macros are forbidden</li>
<li>Include another .c is forbidden</li>
<li>Macros with logic (while/if/variables/...) are forbidden</li>
</ul>
<ol start="4">
<li>Your output needs to be respecting the "sorting" criteria and in one column. It will be compared with: <code>ls -1</code>.</li>
</ol>
<pre class=" language-plain"><code class=" language-plain">$&gt;./my_ls &gt; my_ls.output
$&gt;ls -1 &gt; ls.output
$&gt;diff my_ls.output ls.output
$&gt;
</code></pre>
<h3>Tips</h3>
<p>Check /dev
What is the difference between <code>stat</code> and <code>lstat</code>?</p>

<p></p>
</div>

</div>
</div>
</div>
<div class="tab-pane" id="resources" role="tabpanel">
</div>
</div>
</div>
</div>
