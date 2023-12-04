/**
 * @class MP3TaggingService
 * @brief Service for handling MP3 tagging operations.
 *
 * This service uses TagLib to update the tags of MP3 files, including lyrics and other metadata.
 */
#ifndef MP3TAGGINGSERVICE_H
#define MP3TAGGINGSERVICE_H

#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/unsynchronizedlyricsframe.h>
#include <taglib/textidentificationframe.h>
#include <string>

class MP3TaggingService
{
public:
    MP3TaggingService();

    /**
     * Updates the tags of an MP3 file.
     * @param file_path Path to the MP3 file.
     * @param transcription Transcription to be set as lyrics.
     * @param additionalTags Map of additional tag fields and values.
     */
    void updateTags(const std::string &file_path, const std::string &transcription, const std::map<std::string, std::string> &additionalTags);

private:
    void setLyrics(TagLib::MPEG::File &file, const std::string &lyrics);
    void setTextFrame(TagLib::ID3v2::Tag *tag, const char *frameID, const std::string &text);

    // More functions that interact with TagLib to set various ID3 tags if necessary
};

#endif // MP3TAGGINGSERVICE_H