
function fileNameFromPath(path) {
    var pos = path.lastIndexOf('/')
    return path.substring(pos + 1)
}

function readableSize(bytes) {
    if (bytes < 1024)
        return String(bytes) + "B"
    else if (bytes < 1048576)
        return String(Math.round(bytes / 1024)) + "KB"
    else if (bytes < 1073741824)
        return String(Math.round(bytes / 1048576)) + "MB"
    else
        return String(Math.round(bytes / 1073741824)) + "GB"
}

function iconSource(icon) {
    if (icon === "page_white_acrobat")
        return "image://theme/icon-m-content-pdf"
    else if (icon === "page_white_picture")
        return "image://theme/icon-m-content-image"
    else if (icon === "folder" || icon === "folder_user")
        return "image://theme/icon-m-common-directory"
    else if (icon === "folder_public")
        return "image://theme/icon-m-common-directory"
    else if (icon === "folder_photos")
        return "image://theme/icon-m-content-photoalbum"
    else
        return "image://theme/icon-m-content-document"
}
