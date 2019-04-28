由于我个人平时常使用C/C++进行编程，所以我决定把CentOS下面的VIM这个强大的编辑器改造成一个强大的C++的IDE。下面是具体的步骤。

### 安装pathogen
该插件地址为：
https://github.com/tpope/vim-pathogen

安装命令为：
```

mkdir -p ~/.vim/autoload ~/.vim/bundle && \
curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim
```

安装完成之后，打开~/.vimrc文件，然后输入：
```
execute pathogen#infect()
syntax on
filetype plugin indent on
```
然后保存退出，这个插件就安装完成了。此时如果在~/.vim文件夹里面执行tree命令，则会得到这样的结果：


.
├── autoload
│   └── pathogen.vim
└── bundle

这里面autoload这个目录存放的就是我们的这个pathogen这个插件，其实这个插件就是一个脚本。当vim启动时，由于刚刚我们在~/.vimrc里面配置了`execute pathogen#infect()`这个功能，所以它会自动加载这个脚本并执行里面的函数。

### 安装auto-pairs插件

项目地址：
https://github.com/jiangmiao/auto-pairs

它的功能是成对插入或删除括号，引号等。安装方式如下：

```
git clone git://github.com/jiangmiao/auto-pairs.git ~/.vim/bundle/auto-pairs
```

### 安装NERDTree

功能：显示目录树

项目地址：
https://github.com/scrooloose/nerdtree

安装：
```
git clone https://github.com/scrooloose/nerdtree.git ~/.vim/bundle/nerdtree
```
为了方便打开NERDTree，我们可以设置快捷键，还是打开~/.vimrc，插入下面一行
```
map <C-n> :NERDTree<CR>
```

### MiniBufExplorer
功能：显示已经打开的buffer
项目地址：
https://www.vim.org/scripts/script.php?script_id=159

安装：
```
mkdir -p ~/.vim/bundle/minibufexplorer/plugin && wget "http://www.vim.org/scripts/download_script.php?src_id=3640" -O ~/.vim/bundle/minibufexplorer/plugin/minibufexpl.vim
```
命令解释：在~/.vim/bundle中新建一个目录minibufexplorer，并在其中创建一个plugin，然后下载网址中的内容，-O表示指定下载目录和文件名如后面所示。然后我们打开两个文件，可以看到如图所示上面有了一个标志。

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/linux/asset/minibufexplorer.png)

在~/.vimrc文件中插入下面一行：

```
let g:miniBufExplMaxSize = 2
```

### ctags+taglist+omnicppcomplete

**1.首先安装ctags**

执行以下命令：
```
sudo yum install ctags
```

创建索引：在你代码的根目录执行如下命令，会生成一个tags文件，此时在代码根目录下打开一个文件（vim默认只加载工作目录下的tags文件），将光标置于一个函数或结构体名字上，按ctr+]即可跳转到该名称的定义处，如果出现多个选项，可以输入编号选择对应跳转的地方，按ctr+o可回到光标之前的位置。
ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++

**2.安装taglist**

功能：可以将代码内的函数、变量等按照规律列出来，方便查找。

下载地址：
http://www.vim.org/scripts/script.php?script_id=273

安装：
```
cd ~/.vim/bundle && wget "http://www.vim.org/scripts/download_script.php?src_id=19574" -O taglist.zip && unzip taglist.zip -d taglist
```
命令意义：改变当前目录为~/.vim/bundle，然后下载压缩包并命名为taglist.zip，然后将压缩包解压到taglist文件夹中。

打开~/.vimrc，输入以下内容：

```
let Tlist_Show_One_File=1 " 只展示一个文件的taglist
let Tlist_Exit_OnlyWindow=1 " 当taglist是最后以个窗口时自动退出
let Tlist_Use_Right_Window=1 " 在右边显示taglist窗口
let Tlist_Sort_Type="name" " tag按名字排序
```


**3.OmniCppComplete

对C++语法补全的插件，可以对function、namespace、class member等进行补全。omni补全需要依赖tags文件，需要你用ctags命令自己生成。

下载地址：
http://www.vim.org/scripts/script.php?script_id=1520

安装：
```
cd ~/.vim/bundle && wget "http://www.vim.org/scripts/download_script.php?src_id=7722" -O omnicppcomplete.zip && unzip omnicppcomplete.zip -d omnicppcomplete
```
由于命令格式和上面的一致，所以这里不再解释。该命令还需要进行以下配置，打开~/.vimrc文件，输入

```
filetype plugin indent on
set completeopt=longest,menu
let OmniCpp_NamespaceSearch = 2     " search namespaces in the current buffer   and in included files
let OmniCpp_ShowPrototypeInAbbr = 1 " 显示函数参数列表
let OmniCpp_MayCompleteScope = 1    " 输入 :: 后自动补全
let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]
```

前面说过，omni插件的补全是依赖于tags文件的，因此需要我们手动建立tags文件，方法见前面所示。


当输入hello.h和hello.cpp中的函数或结构体时，通过按`ctr+x` `ctr+o`就可以自动补全了。
通过按`ctr+n`和`ctr+p`可以对候选项进行上下选择。通过这种方式可以实现对函数、结构体的补全。
另外，我们还可以实现对STL补全，这才是我们需要的。

**4.对STL补全**

执行以下命令：

```
mkdir -p ~/.vim/tags && cd ~/.vim/tags && wget "http://www.vim.org/scripts/download_script.php?src_id=9178" -O - | tar jxvf -
```
然后我们在~/.vim/tags/cpp_src目录下执行ctags命令：
```
ctags -R --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++
```

然后打开~/.vimrc添加下面一行：
```
set tags+=~/.vim/tags/cpp_src/tags
```
这种方式显然是不友好的，需要使用ctrl+x和ctrl+o，所以我们可以学习shell中使用TAB补全的方式进行补全，这里就需要使用到SuperTAB。

### SuperTab

项目地址：
https://github.com/ervandew/supertab

安装：

```
cd ~/.vim/bundle && git clone https://github.com/ervandew/supertab.git ~ /.vim/bundle/supertab
```

无需任何配置即可使用，这时你想要补全变量名或函数名只需按一下TAB键即可，出现候选窗口之后也可以用TAB键进行选择。
注意：由于TAB键被映射成了补全快捷键，也就无法通过TAB键直接输入制表符，这时如果想要输入制表符可以通过`ctr+v TAB`即可，即先输入`ctr+v`再输入`TAB`键，在vim下通过`ctl+v`可以输入很多不可见字符，比如试试`ctr+v` `ctr+w`。

### 安装colorschemes

功能：可以给vim更换配色方案

项目地址：

https://github.com/flazz/vim-colorschemes

安装：
```
cd ~/.vim/bundle && git clone 
https://github.com/flazz/vim-colorschemes.git ~ /.vim/bundle/colorschemes
```
在`~/.vim/colors`中有许多配色方案，你可以任选其一来应用。例如我们使用molokai这个配色方案，我们可以在~/.vimrc中添加这个语句：
```
colorscheme molokai
```

以上，就搭建成功了一个功能强大的C/C++的IDE。