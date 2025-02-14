/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <HCCEnvironment.h>
#include <HCCIO.h>
#include <HCCGuid.h>
#include <HTEngine.h>
#include <HCCApplication.h>

using namespace Harlinn;
using namespace Harlinn::Common::Core;

AnsiString GetDatabaseDir( )
{
    auto TestDataRoot = Environment::EnvironmentVariable( "HCC_TEST_DATA_ROOT" );
    auto directoryPath = IO::Path::Combine( TestDataRoot, "\\LMDB" );

    if ( IO::Directory::Exist( directoryPath ) == false )
    {
        IO::Directory::Create( directoryPath );
    }
    return directoryPath;
}

int main()
{
    auto applicationOptions = std::make_shared<ApplicationOptions>( );
    applicationOptions->Load( );
    auto application = std::make_shared<Application>( applicationOptions );
    application->Start( );

    using Engine = Timeseries::Engine<>;
    using Point = typename Engine::Point;
    using TimeseriesCursor = typename Engine::TimeseriesCursor;
    DateTime timestamp1( 2020, 1, 1 ), timestamp2( 2020, 1, 2 ),
        timestamp3( 2020, 1, 3 ), timestamp4( 2020, 1, 4 );

    auto DatabaseDir = GetDatabaseDir( );
    printf( "Database directory:%s\n", DatabaseDir.c_str( ) );
    Timeseries::TimeseriesEngineOptions options( DatabaseDir, true );
    auto timeseriesId1 = Test::Ids[0];

    Engine engine( options );
    auto transaction = engine.BeginTransaction( );
    auto timeseriesCursor = transaction.OpenTimeseries( timeseriesId1 );

    timeseriesCursor.Insert( timestamp1, 1 );
    timeseriesCursor.Insert( timestamp2, 2 );
    timeseriesCursor.Insert( timestamp3, 3 );
    timeseriesCursor.Insert( timestamp4, 4 );

    if ( timeseriesCursor.MoveFirst( ) )
    {
        do
        {
            auto& current = timeseriesCursor.Current( );
            std::cout << "Timestamp: " << current.Timestamp( ) 
                << ", Flags: " << current.Flags( ) 
                << ", Value: " << current.Value( ) << std::endl;
        } while ( timeseriesCursor.MoveNext( ) );
    }
    DateTime timestamp( 2020, 1, 2, 12, 0, 0 );
    auto found = timeseriesCursor.Search( timestamp );
    if ( found )
    {
        auto& current = timeseriesCursor.Current( );
        std::cout << "Found Timestamp: " << current.Timestamp( )
            << ", Flags: " << current.Flags( )
            << ", Value: " << current.Value( ) << std::endl;
    }


    timeseriesCursor.Close( );
    transaction.Commit( );

    application->Stop( );
}
