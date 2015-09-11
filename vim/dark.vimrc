"turn on syntax highlighting
syntax on

"basic configurations
set tabstop=4
set shiftwidth=4
set softtabstop=4
set cindent shiftwidth=4
set smarttab
set expandtab
set autoindent
set number
set background=dark
set ttyfast

"recursive map in insert and command modes
"map! jk <esc>
"map! jj <esc>
noremap <c-k> <c-w>

"hight current line
set cursorline
"highlight CursorLine cterm=NONE ctermbg=LightGreen ctermfg=NONE
"highlight CursorLine cterm=NONE ctermbg=LightYellow ctermfg=NONE
highlight CursorLine cterm=NONE ctermbg=DarkGrey ctermfg=NONE
"set cursorcolumn
highlight CursorColumn cterm=NONE ctermbg=DarkGrey ctermfg=NONE

