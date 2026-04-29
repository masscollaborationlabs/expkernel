# PSD GNU/Linux
#
# Copyright (C) 2026 Mass Collaboration Labs
# Copyright (C) 2026 PSD Authors
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

.intel_syntax noprefix

.section .text
.code32
.global _start
.extern kernel_main

_start:
    call kernel_main
1:
    cli
    hlt
    jmp 1b

.section .note.GNU-stack,"",@progbits
