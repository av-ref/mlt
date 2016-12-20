



#qt5_generate_moc(${TestCase}.cpp ${TestCase}.moc)

add_executable(${TestCase} ${TestCase}.cpp )

target_link_libraries(${TestCase} mlt++ mlt Qt5::Widgets Qt5::Core Qt5::Test)
