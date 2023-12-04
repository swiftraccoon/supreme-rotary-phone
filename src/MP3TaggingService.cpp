#include "../include/MP3TaggingService.h"

MP3TaggingService::MP3TaggingService()
{
    // Initialization, if any, goes here
}

void MP3TaggingService::updateTags(const std::string &file_path, const std::string &transcription, const std::map<std::string, std::string> &additionalTags)
{
    TagLib::FileRef f(file_path.c_str());
    if (!f.isNull() && f.tag())
    {
        auto *tag = f.tag();

        // Set the lyrics to the transcription text
        setLyrics(dynamic_cast<TagLib::MPEG::File &>(*f.file()), transcription);

        // Use additional tags as required
        for (const auto &[key, value] : additionalTags)
        {
            setTextFrame(dynamic_cast<TagLib::ID3v2::Tag *>(tag), key.c_str(), value);
        }

        f.file()->save();
    }
}

void MP3TaggingService::setLyrics(TagLib::MPEG::File &file, const std::string &lyrics)
{
    TagLib::ID3v2::Tag *tag = file.ID3v2Tag(true);
    TagLib::ID3v2::UnsynchronizedLyricsFrame *lyricsFrame = new TagLib::ID3v2::UnsynchronizedLyricsFrame();
    lyricsFrame->setText(TagLib::String(lyrics));
    tag->addFrame(lyricsFrame);
}

void MP3TaggingService::setTextFrame(TagLib::ID3v2::Tag *tag, const char *frameID, const std::string &text)
{
    TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame(frameID, TagLib::String::UTF8);
    frame->setText(TagLib::String(text, TagLib::String::UTF8));
    tag->addFrame(frame);
}

// Implement other methods for setting specific tags as needed